#include "nm.h"

void nm64bits(struct nm *nm)
{
	Elf64_Ehdr	*hdr;
	Elf64_Shdr	*shdr;
	Elf64_Sym	*sym;
	hdr = (Elf64_Ehdr *)nm->map;
	shdr = (Elf64_Shdr *)(nm->map + hdr->e_shoff);
	printf("hdr->e_ehsize: %ld\n", sizeof(Elf64_Ehdr));
	if (hdr->e_ehsize != sizeof(Elf64_Ehdr))
		print_error("file format not recognized", nm);
	int i;
	for (i = 0; i < hdr->e_shnum; i++)
	{
		printf("%d %d\n", shdr[i].sh_name, shdr[i].sh_type);
		printf("%s\n", (char *)(nm->map + shdr[hdr->e_shstrndx].sh_offset + shdr[i].sh_name));
		sym = (Elf64_Sym *)(nm->map + shdr[i].sh_offset);
		printf("sym->st_name: %d\n", sym->st_name);
		if (shdr[i].sh_type == SHT_SYMTAB)
			break;
	}
	printf("%d\n", hdr->e_type);
	printf("64 bits\n");
	printf("e_ehsize: %d\n", hdr->e_shentsize);
	printf("e_shnum: %d\n", hdr->e_shnum);
	printf("e_shstrndx: %d\n", hdr->e_shstrndx);
	printf("ev_current %d %d\n", hdr->e_version, EV_CURRENT);
}
