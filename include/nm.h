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
#include <stdbool.h>

typedef struct nm
{
	int fd;
	void *map;
	struct stat buf;
	char *filename;
	int count;
} nm;

typedef struct section
{
	char *name;
	char sym;
	unsigned long value;
} section;

/* nm program*/
void	ft_nm(nm *nm);
int		nm64bits(nm *nm, section ***sect);
int		nm32bits(nm *nm, section ***sect);
int		print_error(char *msg, nm *nm);

/* Function lib */
char*	ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);

#endif
