#include "nm.h"

char **nm32bits(struct nm *nm)
{
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)nm->map;
	Elf32_Shdr *shdr = (Elf32_Shdr *)(nm->map + ehdr->e_shoff);
	const char *shstrtab = (const char *)(nm->map + shdr[ehdr->e_shstrndx].sh_offset);
	char **functions = NULL;
	size_t count = 0;

	Elf32_Shdr *symtab = NULL, *strtab = NULL;
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		const char *section_name = shstrtab + shdr[i].sh_name;
		if (ft_strcmp(section_name, ".symtab") == 0)
		{
			symtab = &shdr[i];
		}
		else if (ft_strcmp(section_name, ".strtab") == 0)
		{
			strtab = &shdr[i];
		}
	}

	if (!symtab || !strtab)
		print_error("Table des symboles ou chaînes introuvable\n", nm);

	Elf32_Sym *symbols = (Elf32_Sym *)(nm->map + symtab->sh_offset);
	const char *strtab_data = (const char *)(nm->map + strtab->sh_offset);
	size_t symbol_count = symtab->sh_size / sizeof(Elf32_Sym);

	printf("Symbol table '.symtab' contains %zu entries:\n", symbol_count);
	printf("Num:    Value          Size Type    Bind   Vis      Ndx Name\n");
	for (size_t i = 0; i < symbol_count; i++)
	{
		const char *symbol_name = strtab_data + symbols[i].st_name;
		if (symbols[i].st_name != 0)
		{
			printf("   %3zu: 000000000000%lx, %lu, %d, %d,%d, %s\n", \
				i, symbols[i].st_value, symbols[i].st_size, \
				ELF32_ST_TYPE(symbols[i].st_info), ELF32_ST_BIND(symbols[i].st_info), \
				symbols[i].st_shndx, symbol_name);
		}

		// Ajouter les symboles de type fonction à la liste
		if (ELF32_ST_TYPE(symbols[i].st_info) == STT_FUNC && symbols[i].st_name != 0)
		{
			functions = realloc(functions, sizeof(char *) * (count + 1));
			functions[count] = ft_strdup(symbol_name);
			count++;
		}
	}

	return functions;
}
