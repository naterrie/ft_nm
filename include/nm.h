#ifndef NM_H
#define NM_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <elf.h>

void ft_nm(void *map);
void print_error(char *msg);

#endif
