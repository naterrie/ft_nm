#include "nm.h"

static char found_sym64(Elf64_Sym *sym, Elf64_Shdr *shdr, char *SectionName)
{
	unsigned int bind;
	unsigned int type;
	unsigned int idx = sym->st_shndx;

	bind = ELF64_ST_BIND(sym->st_info);
	type = ELF64_ST_TYPE(sym->st_info);
	if (bind == STB_GNU_UNIQUE) return ('u');
	if (type == STT_GNU_IFUNC) return ('i');
	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
			return ((idx == SHN_UNDEF) ? 'v' : 'V');
		return ((idx == SHN_UNDEF) ? 'w' : 'W');
	}
	if (type == STT_FILE) return ('a');
	if (idx == SHN_ABS) return ('A');
	if (idx == SHN_COMMON) return ('C');
	if (idx == SHN_UNDEF) return ('U');

	if (shdr->sh_type == SHT_NOBITS) return ((bind == STB_LOCAL) ? 'b' : 'B');
	if (shdr->sh_flags & SHF_EXECINSTR) return ((bind == STB_LOCAL) ? 't' : 'T');
	if (!(shdr->sh_flags & SHF_WRITE))
	{
		if ((shdr->sh_flags & SHF_EXECINSTR) && (shdr->sh_flags & SHF_ALLOC))
			return ((bind == STB_LOCAL) ? 't' : 'T');
		if (shdr->sh_type == SHT_GROUP)
			return ('n');

		if (ft_strncmp(SectionName, ".debug", 6) == 0)
			return ('N');
		return ((bind == STB_LOCAL) ? 'r' : 'R');
	}
	return ((bind == STB_LOCAL) ? 'd' : 'D');
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
		if ((symbol_name == NULL || symbol_name[0] == '\0') && nm->flags.a && symbols[i].st_shndx < ehdr->e_shnum)
			symbol_name = shdrtab + shdr[symbols[i].st_shndx].sh_name;
		if (symbol_name == NULL)
		{
			free((*sect)[count]);
			continue;
		}
		(*sect)[count]->name = ft_strdup(symbol_name);
		if ((*sect)[count]->name == NULL)
			return 1;
		(*sect)[count]->sym = found_sym64(&symbols[i], &shdr[symbols[i].st_shndx], (*sect)[count]->name);

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
