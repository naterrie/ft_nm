#include "nm.h"

void	check_double(section **sections)
{
	section *tmp;
	int	i;

	i = 0;
	while(sections[i + 1])
	{
		if (ft_strcmp(sections[i]->name, sections[i + 1]->name) == 0)
		{
			if (sections[i]->value > sections[i + 1]->value)
			{
				tmp = sections[i];
				sections[i] = sections[i + 1];
				sections[i + 1] = tmp;
			}
		}
		i++;
	}
}

void	display_section(section **section, int bit, flag *flags)
{
	check_double(section);
	for (int i = 0; section[i]; i++)
	{
		if (ft_strlen(section[i]->name) == 0 && section[i]->value == 0 && section[i]->sym != 'a')
			continue ;
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
	if (flags->r == true)
		reverse_sort(sections, bit, flags);
	else
		display_section(sections, bit, flags);
}

void	reverse_sort(section **sections, int bit, flag *flags)
{
	section *tmp;
	int count = 0;
	int i;
	int j;

	while (sections[count])
		count++;
	i = 0;
	j = count - 1;
	while (i < j)
	{
		tmp = sections[i];
		sections[i] = sections[j];
		sections[j] = tmp;
		i++;
		j--;
	}
	display_section(sections, bit, flags);
}
