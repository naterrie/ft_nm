#include "nm.h"

static char found_sym(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
	int type = ELF64_ST_TYPE(sym->st_info);
	int bind = ELF64_ST_BIND(sym->st_info);

	if (bind == STB_GNU_UNIQUE)
		return 'u';
	else if (type == STT_GNU_IFUNC)
		return 'i';
	else if (sym->st_shndx == SHN_UNDEF)
	{
		if (bind == STB_WEAK)
			return (type == STT_OBJECT) ? 'v' : 'w';
		return 'U';
	}
	else if (sym->st_shndx == SHN_ABS)
		return 'a';
	else if (sym->st_shndx >= SHN_LORESERVE)
		return '?';

	Elf64_Shdr *section = &shdr[sym->st_shndx];
	if (section->sh_type == SHT_NOBITS && section->sh_flags == (SHF_ALLOC | SHF_WRITE))
		return (bind == STB_LOCAL) ? 'b' : 'B';
	else if (section->sh_type == SHT_PROGBITS && section->sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		return (bind == STB_LOCAL) ? 't' : 'T';
	else if (section->sh_type == SHT_PROGBITS && section->sh_flags == (SHF_ALLOC | SHF_WRITE))
		return (bind == STB_LOCAL) ? 'd' : 'D';
	else if (section->sh_type == SHT_PROGBITS && section->sh_flags == SHF_ALLOC)
		return (bind == STB_LOCAL) ? 'r' :'R';

	if (bind == STB_WEAK)
		return 'W';
	return '?';
}

int nm64bits(nm *nm, section ***sect)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)nm->map;
	if (ehdr->e_shoff >= (Elf64_Off)nm->buf.st_size)
		return print_error("file format not recognized", nm);

	if (ehdr->e_shnum * ehdr->e_shentsize + ehdr->e_shoff > (size_t)nm->buf.st_size)
		return print_error("file format not recognized", nm);

	if (ehdr->e_shentsize != sizeof(Elf64_Shdr))
		return print_error("file format not recognized", nm);

	Elf64_Shdr *shdr = (Elf64_Shdr *)(nm->map + ehdr->e_shoff);
	const char *shdrtab = (const char *)(nm->map + shdr[ehdr->e_shstrndx].sh_offset);

	Elf64_Shdr *symtab = NULL, *strtab = NULL;
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		const char *sectionName = shdrtab + shdr[i].sh_name;

		if (ft_strcmp(sectionName, ".symtab") == 0)
			symtab = &shdr[i];
		else if (ft_strcmp(sectionName, ".strtab") == 0)
			strtab = &shdr[i];
	}

	if (!symtab || !strtab)
		return print_error("file format not recognized", nm);

	Elf64_Sym *symbols = (Elf64_Sym *)(nm->map + symtab->sh_offset);
	const char *strtab_data = (const char *)(nm->map + strtab->sh_offset);
	size_t symbol_count = symtab->sh_size / sizeof(Elf64_Sym);

	*sect = malloc(sizeof(section*) * (symbol_count + 1));
	if (*sect == NULL)
		return 1;
	int count = 0;

	for (size_t i = 1; i < symbol_count; i++)
	{
		const char *symbol_name = strtab_data + symbols[i].st_name;
		(*sect)[count] = malloc(sizeof(section));
		if ((*sect)[count] == NULL)
			return 1;
		(*sect)[count]->name = ft_strdup(symbol_name);
		(*sect)[count]->sym = found_sym(&symbols[i], shdr);

		if (symbols[i].st_shndx == SHN_ABS)
			(*sect)[count]->value = 0;
		else if (symbols[i].st_shndx == SHN_UNDEF)
			(*sect)[count]->value = -1;
		else
			(*sect)[count]->value = symbols[i].st_value;
		count++;

	}

	nm->count = count;
	(*sect)[count] = NULL;
	return 0;
}
