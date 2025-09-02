#include "nm.h"

void	no_sort(section **section, int bit, flag *flags)
{
	for (int i = 0; section[i]; i++)
	{
		if (flags->a == false && section[i]->sym == 'a')
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
void	default_sort(section **sections, int bit, flag *flags) // duplicata of no_sort for future modification
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
				//printf("swap %s and %s\n", sections[i]->name, sections[j]->name);
				tmp = sections[i];
				sections[i] = sections[j];
				sections[j] = tmp;
			}
		}
	}
	// Call the no_sort function with the sorted sections
	no_sort(sections, bit, flags);
}
