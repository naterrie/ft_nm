#include "nm.h"



static void	init_nm(struct nm *nm)
{
	nm->fd = -1;
	nm->map = NULL;
	nm->filename = "a.out";
}

static int	map_file(nm *nm)
{
	nm->fd = open(nm->filename, O_RDONLY);
	if (nm->fd == -1)
		return print_error("No such file", nm);

	if (fstat(nm->fd, &nm->buf) == -1)
		return print_error("Error fatal", nm);

	nm->map = mmap(NULL, nm->buf.st_size, PROT_READ, MAP_PRIVATE, nm->fd, 0);
	if (nm->map == MAP_FAILED)
		return print_error("Error fatal", nm);
	close(nm->fd);
	return 0;
}

int main(int argc, char **argv)
{
	struct nm nm;
	init_nm(&nm);

	int i = 1;
	if (argc == 1)
	{
		nm.filename = "a.out";
		if (map_file(&nm) != 1)
			ft_nm(&nm);
		else
			return print_error("Error fatal", &nm);
		munmap(nm.map, nm.buf.st_size);
		return (0);
	}

	while (i < argc)
	{
		nm.filename = argv[i];
		if (map_file(&nm) != 1)
			ft_nm(&nm);
		else
			return print_error("Error fatal", &nm);
		munmap(nm.map, nm.buf.st_size);
		i++;
		if (i < argc)
			write(1, "\n", 1);
	}

	return (0);
}
