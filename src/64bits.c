#include "nm.h"

void nm64bits(struct nm *nm)
{
	Elf64_Ehdr	*hdr;

	hdr = (Elf64_Ehdr *)nm->map;
	if (hdr->e_ehsize != sizeof(Elf64_Ehdr))
		print_error("file format not recognized", nm);

}
