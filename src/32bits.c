#include "nm.h"

void nm32bits(struct nm *nm)
{
	Elf32_Ehdr	*hdr;

	hdr = (Elf32_Ehdr *)nm->map;
	if (hdr->e_ehsize != sizeof(Elf32_Ehdr))
		print_error("file format not recognized", nm);
	printf("32 bits\n");
	printf("e_ehsize: %d\n", hdr->e_shentsize);
	printf("e_shnum: %d\n", hdr->e_shnum);
	printf("e_shstrndx: %d\n", hdr->e_shstrndx);
	printf("ev_current %d %d\n", hdr->e_version, EV_CURRENT);
}
