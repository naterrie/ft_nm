#ifndef NM_H
# define NM_H

#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <elf.h>

typedef struct flag
{
	bool a;
	bool g;
	bool u;
	bool r;
	bool p;
} flag;

typedef struct nm
{
	int fd;
	void *map;
	struct stat buf;
	char *filename;
	int count;
	flag flags;
} nm;

typedef struct section
{
	char *name;
	char sym;
	long value;
} section;

/* nm program */
int		ft_nm(nm *nm);
int		nm64bits(nm *nm, section ***sect);
int		nm32bits(nm *nm, section ***sect);

/* Sorting */
void	no_sort(section **section, int j, flag *flags);
void	default_sort(section **section, int j, flag *flags);

/* Utils */
void 	put_value(long value, int is_64bit);
void	free_section(section **sect);
int		print_error(char *msg, nm *nm);

/* Function lib */
char*	ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);

#endif
