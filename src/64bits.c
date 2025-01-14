#include "nm.h"

void nm64bits(struct nm *nm)
{
	Elf64_Ehdr	*hdr;
	Elf64_Shdr	*shdr;
	hdr = (Elf64_Ehdr *)nm->map;
	shdr = (Elf64_Shdr *)(nm->map + hdr->e_shoff);
	printf("hdr->e_ehsize: %ld\n", sizeof(Elf64_Ehdr));
	if (hdr->e_ehsize != sizeof(Elf64_Ehdr))
		print_error("file format not recognized", nm);

}
