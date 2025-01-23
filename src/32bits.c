#include "nm.h"

static char found_sym(Elf32_Sym *sym, Elf32_Shdr *shdr)
{
	int type = ELF32_ST_TYPE(sym->st_info);
	int bind = ELF32_ST_BIND(sym->st_info);
	(void)shdr;
	(void)sym;
	(void)type;
	(void)bind;
	char c = '?';
	return c;
}

int nm32bits(nm *nm, section ***sect)
{
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)nm->map;
	if (ehdr->e_shoff >= (Elf32_Off)nm->buf.st_size)
		return print_error("file format not recognized", nm);

	if (ehdr->e_shnum * ehdr->e_shentsize + ehdr->e_shoff > (size_t)nm->buf.st_size)
		return print_error("file format not recognized", nm);

	if (ehdr->e_shentsize != sizeof(Elf32_Shdr))
		return print_error("file format not recognized", nm);

	Elf32_Shdr *shdr = (Elf32_Shdr *)(nm->map + ehdr->e_shoff);
	const char *shdrtab = (const char *)(nm->map + shdr[ehdr->e_shstrndx].sh_offset);

	Elf32_Shdr *symtab = NULL, *strtab = NULL;
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

	Elf32_Sym *symbols = (Elf32_Sym *)(nm->map + symtab->sh_offset);
	const char *strtab_data = (const char *)(nm->map + strtab->sh_offset);
	size_t symbol_count = symtab->sh_size / sizeof(Elf32_Sym);

	*sect = malloc(sizeof(section*) * (symbol_count + 1));
	if (*sect == NULL)
		return 1;
	int count = 0;

	for (size_t i = 0; i < symbol_count; i++)
	{
		const char *symbol_name = strtab_data + symbols[i].st_name;
		if (symbols[i].st_name != 0)
		{
			(*sect)[count] = malloc(sizeof(section));
			if ((*sect)[count] == NULL)
				return 1;
			(*sect)[count]->name = ft_strdup(symbol_name);
			(*sect)[count]->sym = found_sym(&symbols[i], shdr);

			if (symbols[i].st_shndx == SHN_ABS)
				(*sect)[count]->value = 0000;
			else if (symbols[i].st_shndx == SHN_UNDEF)
				(*sect)[count]->value = -1;
			else
				(*sect)[count]->value = symbols[i].st_value;
			count++;
		}
	}

	nm->count = count;
	(*sect)[count] = NULL;
	return 0;
}


/* char found_sym(Elf32_Sym *sym, Elf32_Shdr *shdr)
{
	int type = ELF32_ST_TYPE(sym->st_info);
	int bind = ELF32_ST_BIND(sym->st_info);
}
 Voici ma fonction me renvoi ma lettre pour ressembler a nm (les lettres expliques via ce document : https://sourceware.org/binutils/docs/binutils/nm.html) */
