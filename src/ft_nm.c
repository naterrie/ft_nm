#include "nm.h"

/*
	checking the file if is an executable, check if is 64 or 32 bytes
*/

void ft_nm(void *map)
{
	unsigned char *magic = (unsigned char *)map;
	if (magic[EI_MAG0] != 0x7F || magic[EI_MAG1] != ELFMAG1 \
		|| magic[EI_MAG2] != ELFMAG2 || magic[EI_MAG3] != ELFMAG3)
		print_error("not an object file");

	if (magic[EI_CLASS] == ELFCLASS64)
		printf("64bits\n");
	else if (magic[EI_CLASS] == ELFCLASS32)
		printf("32bits\n");
}
