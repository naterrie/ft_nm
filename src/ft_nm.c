#include "nm.h"

int ft_nm(nm *nm)
{
	unsigned char *magic = (unsigned char *)nm->map;
	section** sect = NULL;

	if (magic[EI_MAG0] != 0x7F || magic[EI_MAG1] != 0x45 || \
		magic[EI_MAG2] != 0x4c || magic[EI_MAG3] != 0x46)
	{
		print_error("file format not recognized", nm);
		return 1;
	}

	if (magic[EI_CLASS] == ELFCLASS64)
	{
		if (nm64bits(nm, &sect) == 1)
			return 1;
	}
	else if (magic[EI_CLASS] == ELFCLASS32)
	{
		if (nm32bits(nm, &sect) == 1)
			return 1;
	}
	else
	{
		print_error("file format not recognized", nm);
		return 1;
	}
	if (nm->flags.p == true)
		display_section(sect, (magic[EI_CLASS] == ELFCLASS64) ? 1 : 0, &nm->flags);
	else
		default_sort(sect, (magic[EI_CLASS] == ELFCLASS64) ? 1 : 0, &nm->flags);
	free_section(sect);
	return 0;
}
