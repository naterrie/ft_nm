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
	{
		write(2, "ft_nm: '", 7);
		write(2, nm->filename, ft_strlen(nm->filename));
		write(2, "': No such file\n", 16);
		return 1;
	}

	if (fstat(nm->fd, &nm->buf) == -1)
		return print_error("Error fatal", nm);

	nm->map = mmap(NULL, nm->buf.st_size, PROT_READ, MAP_PRIVATE, nm->fd, 0);
	if (nm->map == MAP_FAILED)
		return print_error("Error fatal", nm);
	close(nm->fd);
	return 0;
}

void	get_args(nm *nm, int argc, char **argv, bool *hasarg)
{
	int i = 1;

	while (i < argc && argv[i][0] == '-')
	{
		*hasarg = true;
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
	// Order args only symbol: U > G > A
	// Order sort : P > R

	if (nm->flags.u == true && nm->flags.g == true) // u > g
		nm->flags.g = false;
	if (nm->flags.u == true && nm->flags.a == true) // u > a
		nm->flags.a = false;
	if (nm->flags.g == true && nm->flags.a == true) // g > a
		nm->flags.a = false;

	if (nm->flags.p == true && nm->flags.r == true) // p > r
		nm->flags.r = false;
}

void	print_multiple(int argc, char **argv, int i, bool hasarg)
{
	// todo
	if (i == 1 && hasarg == true)
		return ;
	else if (argc > 3 && hasarg == true)
	{
		write(1, "\n", 1);
		write(1, argv[i], ft_strlen(argv[i]));
		write(1, ":\n", 2);
	}
	else if (argc > 2 && hasarg == false)
	{
		write(1, "\n", 1);
		write(1, argv[i], ft_strlen(argv[i]));
		write(1, ":\n", 2);
	}
}

int	main(int argc, char **argv)
{
	struct nm nm;
	int	ret = 0;
	bool hasarg = false;

	init_nm(&nm);
	get_args(&nm, argc, argv, &hasarg);

	if (argc == 1 || (argc == 2 && hasarg == true))
	{
		if (map_file(&nm) != 1)
			ret = ft_nm(&nm);
		else
			ret = 1;
	}
	else
	{
		int i = 1;
		if (hasarg == true)
			i++;
		while (i < argc)
		{
			nm.filename = argv[i];
			if (map_file(&nm) == 0)
			{
				print_multiple(argc, argv, i, hasarg);
				ret = ft_nm(&nm);
			}
			else
				ret = 1;
			munmap(nm.map, nm.buf.st_size);
			i++;
			// if (i < argc)
			// 	write(1, "\n", 1);
		}
	}
	return (ret);
}
