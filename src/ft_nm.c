#include "nm.h"

/*
	checking the file if is an executable, check if is 64 or 32 bytes
*/

void ft_nm(struct nm *nm)
{
	unsigned char *magic = (unsigned char *)nm->map;

	if (magic[EI_MAG0] != 0x7F || magic[EI_MAG1] != 0x45 || \
		magic[EI_MAG2] != 0x4c || magic[EI_MAG3] != 0x46)
		print_error("file format not recognized", nm);

	if (magic[EI_CLASS] == ELFCLASS64)
		nm64bits(nm);
	else if (magic[EI_CLASS] == ELFCLASS32)
		nm32bits(nm);
	else
		print_error("file format not recognized", nm);
}
