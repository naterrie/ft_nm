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
void	default_sort(section **section, int bit, flag *flags);
void	no_sort(section **section, int bit, flag *flags);

/* Utils */
int	cmp_section(const char *s1, const char *s2);
void 	put_value(long value, int is_64bit);
int		print_error(char *msg, nm *nm);
void	free_section(section **sect);

/* Function lib */
int		ft_strcmp(const char *s1, const char *s2);
char*	ft_strdup(const char *s);
size_t	ft_strlen(const char *s);

#endif
