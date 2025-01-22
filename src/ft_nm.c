#include "nm.h"

void ft_nm(nm *nm)
{
	unsigned char *magic = (unsigned char *)nm->map;
	section** sect = NULL;

	if (magic[EI_MAG0] != 0x7F || magic[EI_MAG1] != 0x45 || \
		magic[EI_MAG2] != 0x4c || magic[EI_MAG3] != 0x46)
	{
		print_error("file format not recognized", nm);
		return ;
	}

	if (magic[EI_CLASS] == ELFCLASS64)
	{
		if (nm64bits(nm, &sect) == 1)
			return ;
	}
	else if (magic[EI_CLASS] == ELFCLASS32)
	{
		if (nm32bits(nm, &sect) == 1)
			return;
	}
	else
		print_error("file format not recognized", nm);

	for (int i = 0; i < nm->count; i++)
	{
		if (sect[i])
			printf("%lx, %d, %s\n", sect[i]->value, sect[i]->sym, sect[i]->name);
	}
}
