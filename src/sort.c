#include "nm.h"

void	no_sort(section **section, int bit, flag *flags)
{
	for (int i = 0; section[i]; i++)
	{
		if (flags->a == false && section[i]->sym == 'a')
			continue ;
		if (flags->u == true && (section[i]->sym != 'U' && section[i]->sym != 'w'))
			continue ;
		if (flags->g == true && ((section[i]->sym >= 'a' && section[i]->sym <= 'z' && section[i]->sym != 'w')))
			continue ;
		put_value(section[i]->value, bit);
		write(1, " ", 1);
		write(1, &section[i]->sym, 1);
		write(1, " ", 1);
		write(1, section[i]->name, ft_strlen(section[i]->name));
		write(1, "\n", 1);
	}
}
#include <stdio.h>
void	default_sort(section **sections, int bit, flag *flags)
{
	section *tmp;
	int i;
	int j;

	i = 0;
	j = 1;
	for (i = 0; sections[i]; i++)
	{
		for (j = i + 1; sections[j]; j++)
		{
			if (cmp_section(sections[i]->name, sections[j]->name) > 0)
			{
				tmp = sections[i];
				sections[i] = sections[j];
				sections[j] = tmp;
			}
		}
	}
	no_sort(sections, bit, flags);
}
