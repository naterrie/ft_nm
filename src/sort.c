#include "nm.h"

void	no_sort(section **section, int j, flag *flags)
{
	for (int i = 0; section[i]; i++)
	{
		if (flags->a == false && section[i]->sym == 'a')
			continue ;
		put_value(section[i]->value, j);
		write(1, " ", 1);
		write(1, &section[i]->sym, 1);
		write(1, " ", 1);
		write(1, section[i]->name, ft_strlen(section[i]->name));
		write(1, "\n", 1);
	}
}

void	default_sort(section **section, int j, flag *flags) // duplicata of no_sort for future modification
{
	for (int i = 0; section[i]; i++)
	{
		if (flags->a == false && section[i]->sym == 'a')
			continue ;
		put_value(section[i]->value, j);
		write(1, " ", 1);
		write(1, &section[i]->sym, 1);
		write(1, " ", 1);
		write(1, section[i]->name, ft_strlen(section[i]->name));
		write(1, "\n", 1);
	}
}
