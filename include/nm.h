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

/* nm program*/
void	ft_nm(struct nm *nm);
void	print_error(char *msg, struct nm *nm);
char	**nm64bits(struct nm *nm);
char	**nm32bits(struct nm *nm);

/* Function lib */
char*	ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);

#endif
