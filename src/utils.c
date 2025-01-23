/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:31:36 by naterrie          #+#    #+#             */
/*   Updated: 2025/01/23 15:11:08 by naterrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (1);
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
		return (1);
	}
}

void	put_value(long value)
{
	char	*str;
	char	buf[17];
	int		i;

	str = "0123456789abcdef";
	if (value == -1)
		write(1, "                ", 17);
	else
	{
		i = 16;
		while (i != 0)
		{
			buf[i] = str[value % 16];
			value /= 16;
			i--;
		}
		write(1, buf, 17);
	}
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
