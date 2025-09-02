#include "nm.h"

int	print_error(char *msg, struct nm *nm)
{
	write(2, "nm: ", 5);
	write(2, nm->filename, strlen(nm->filename));
	write(2, ": ", 2);
	if (errno != 0)
	{
		write(2, strerror(errno), strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	else
	{
		write(2, msg, strlen(msg));
		write(2, "\n", 1);
		if (nm != NULL)
		{
			if (nm->map != NULL)
				munmap(nm->map, nm->buf.st_size);
			if (nm->fd != -1)
				close(nm->fd);
		}
	}
	return 1;
}

void	put_value(long value, int is_64bit)
{
	char	*str = "0123456789abcdef";
	char	buf[17];
	int		width = is_64bit ? 16 : 8;
	int		i;

	if (value == -1)
	{
		for (i = 0; i < width; i++)
			write(1, " ", 1);
		return;
	}

	for (i = 0; i < width; i++)
		buf[i] = '0';

	i = width - 1;
	while (value != 0 && i >= 0)
	{
		buf[i] = str[value % 16];
		value /= 16;
		i--;
	}
	write(1, buf, width);
}

void	free_section(section **sect)
{
	int	i;

	i = 0;
	while (sect[i])
	{
		free(sect[i]->name);
		free(sect[i]);
		i++;
	}
	free(sect);
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return 1;
	return 0;
}

int	cmp_section(const char *s1, const char *s2)
{
	int	i;
	int	j;
	char c1;
	char c2;
	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		while (s1[i] && !is_alpha(s1[i]))
			i++;
		while (s2[j] && !is_alpha(s2[j]))
			j++;
		c1 = s1[i];
		c2 = s2[j];
		if (c1 >= 'A' && c1 <= 'Z')
			c1 += 32;
		if (c2 >= 'A' && c2 <= 'Z')
			c2 += 32;
		if (c1 != c2)
		{
			if (c1 < c2)
				return -1;
			else
				return 1;
		}
		i++;
		j++;
	}
	if (i < j)
		return -1;
	if (i > j)
		return 1;
	return 0;
}
