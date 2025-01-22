#include "nm.h"

#include <stdio.h>
#include <elf.h>

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
	const char *shstrtab = (const char *)(nm->map + shdr[ehdr->e_shstrndx].sh_offset);

	Elf64_Shdr *symtab = NULL, *strtab = NULL;
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		const char *section_name = shstrtab + shdr[i].sh_name;

		if (ft_strcmp(section_name, ".symtab") == 0)
			symtab = &shdr[i];
		else if (ft_strcmp(section_name, ".strtab") == 0)
			strtab = &shdr[i];
	}
	if (!symtab || !strtab)
		return print_error("Table des symboles ou chaînes introuvable\n", nm);

	Elf64_Sym *symbols = (Elf64_Sym *)(nm->map + symtab->sh_offset);
	const char *strtab_data = (const char *)(nm->map + strtab->sh_offset);
	size_t symbol_count = symtab->sh_size / sizeof(Elf64_Sym);

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
			(*sect)[count]->sym = ELF64_ST_TYPE(symbols[count].st_info);

			(*sect)[count]->value = symbols[count].st_value;
			count++;
		}
	}
	nm->count = count;
	(*sect)[count] = NULL;
	return 0;
}
