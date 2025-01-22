#include "nm.h"

#include <stdio.h>
#include <elf.h>

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
	const char *shstrtab = (const char *)(nm->map + shdr[ehdr->e_shstrndx].sh_offset);

	Elf32_Shdr *symtab = NULL, *strtab = NULL;
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
			// if (symbols[i].st_shndx == SHN_ABS) // flags for absolute symbols
			// 	continue;
			// if (symbols[i].st_value == 0)
			// {
			// 	printf("   %3zu: 0000000000000000, %lu, %d, %d, %d, %s\n",
			// 	i, symbols[i].st_size,
			// ELF32_ST_TYPE(symbols[i].st_info), ELF32_ST_BIND(symbols[i].st_info),
			// 	symbols[i].st_shndx, symbol_name);
			// }
			// else
			// {
				// printf("   %3zu: 000000000000%lx, %lu, %d, %d,%d, %s\n",
				// 	i, symbols[i].st_value, symbols[i].st_size,
				// 	ELF32_ST_TYPE(symbols[i].st_info), ELF32_ST_BIND(symbols[i].st_info),
				// 	symbols[i].st_shndx, symbol_name);
			// }
			(*sect)[count] = malloc(sizeof(section));
			if ((*sect)[count] == NULL)
				return 1;
			(*sect)[count]->name = ft_strdup(symbol_name);
			(*sect)[count]->sym = ELF32_ST_TYPE(symbols[count].st_info);

			(*sect)[count]->value = symbols[count].st_value;
			// printf("%lx, %d, %s\n", (*sect)[count]->value, (*sect)[count]->sym, (*sect)[count]->name);
			count++;
		}
	}
	nm->count = count;
	(*sect)[count] = NULL;

	return 0;
}
