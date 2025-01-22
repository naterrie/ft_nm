#include "nm.h"

int	print_error(char *msg, struct nm *nm)
{
	write(2, "nm: ", 5);
	write(2, nm->filename, strlen(nm->filename));
	write(2, ": ", 2);
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	if (nm != NULL)
	{
		if (nm->map != NULL)
			munmap(nm->map, nm->buf.st_size);
		if (nm->fd != -1)
			close(nm->fd);
	}
	return 1;
}

void init_nm(struct nm *nm)
{
	nm->fd = -1;
	nm->map = NULL;
	nm->filename = "a.out";
}

int	map_file(nm *nm)
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

	if (argc != 1)
		nm.filename = argv[1];

	if (map_file(&nm) != 1)
		ft_nm(&nm);

	munmap(nm.map, nm.buf.st_size);
	
	return (0);
}
