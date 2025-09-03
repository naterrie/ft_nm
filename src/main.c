#include "nm.h"

static void	init_nm(struct nm *nm)
{
	nm->fd = -1;
	nm->map = NULL;
	nm->filename = "a.out";
	nm->count = 0;
	nm->flags.a = false;
	nm->flags.g = false;
	nm->flags.u = false;
	nm->flags.r = false;
	nm->flags.p = false;
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

void	get_args(nm *nm, int argc, char **argv)
{
	int i = 1;

	while (i < argc && argv[i][0] == '-')
	{
		int j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'a')
				nm->flags.a = true;
			else if (argv[i][j] == 'g')
				nm->flags.g = true;
			else if (argv[i][j] == 'u')
				nm->flags.u = true;
			else if (argv[i][j] == 'r')
				nm->flags.r = true;
			else if (argv[i][j] == 'p')
				nm->flags.p = true;
			j++;
		}
		i++;
	}
	if (nm->flags.u == true && nm->flags.a == true)
		nm->flags.a = false;
}

int	main(int argc, char **argv)
{
	struct nm nm;
	init_nm(&nm);
	int ret = 0;

	get_args(&nm, argc, argv);

	if (argc == 1)
	{
		if (map_file(&nm) != 1)
			ret = ft_nm(&nm);
		else
			ret = 1;
	}
	else
	{
		int i = 1;
		while (i < argc)
		{
			if (argv[i][0] == '-')
			{
				i++;
				continue ;
			}
			nm.filename = argv[i];
			if (map_file(&nm) != 1)
				ret = ft_nm(&nm);
			else
			{
				print_error("Error fatal", &nm);
				ret = 1;
			}
			munmap(nm.map, nm.buf.st_size);
			i++;
			if (i < argc)
				write(1, "\n", 1);
		}
	}
	return (ret);
}
