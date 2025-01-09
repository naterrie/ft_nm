#include "nm.h"

/*
	checking the file if is an executable, check if is 64 or 32 bytes
*/

void ft_nm(void *map, struct stat fdstat)
{
	unsigned char *magic = (unsigned char *)map;
	if (magic[EI_MAG0] != 127 || magic[EI_MAG1] != 'E' || magic[EI_MAG2] != 'L' || magic[EI_MAG3] != 'F')
		print_error("not an object file");

	if (magic[EI_CLASS] == 1)
		printf("64bits\n");
	else if (magic[EI_CLASS] == 2)
		printf("32bits\n");

	(void)fdstat;
}
