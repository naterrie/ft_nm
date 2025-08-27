#include "nm.h"

static void	print_sect(section **section, int j)
{
	for (int i = 0; section[i]; i++)
	{
		put_value(section[i]->value, j);
		write(1, " ", 1);
		write(1, &section[i]->sym, 1);
		write(1, " ", 1);
		write(1, section[i]->name, ft_strlen(section[i]->name));
		write(1, "\n", 1);
	}
}

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
		print_sect(sect, 1);
	}
	else if (magic[EI_CLASS] == ELFCLASS32)
	{
		if (nm32bits(nm, &sect) == 1)
			return 1;
		print_sect(sect, 0);
	}
	else
	{
		print_error("file format not recognized", nm);
		return 1;
	}
	free_section(sect);
	return 0;
}
