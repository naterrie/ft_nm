#include "nm.h"

void nm32bits(struct nm *nm)
{
	Elf32_Ehdr	*hdr;

	hdr = (Elf32_Ehdr *)nm->map;
	if (hdr->e_ehsize != sizeof(Elf32_Ehdr))
		print_error("file format not recognized", nm);
}
