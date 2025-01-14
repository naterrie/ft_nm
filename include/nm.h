#ifndef NM_H
# define NM_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <elf.h>

struct nm
{
	int fd;
	void *map;
	struct stat buf;
	char *filename;
};

void ft_nm(struct nm *nm);
void print_error(char *msg, struct nm *nm);
void nm64bits(struct nm *nm);
void nm32bits(struct nm *nm);

#endif
