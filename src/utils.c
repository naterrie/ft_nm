/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:31:36 by naterrie          #+#    #+#             */
/*   Updated: 2025/01/24 13:29:22 by naterrie         ###   ########.fr       */
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


void put_value(long value, int is_64bit)
{
    char    *str = "0123456789abcdef";
    char    buf[17];  // 16 caractères + '\0' pour la terminaison
    int     width = is_64bit ? 16 : 8;  // 64 bits = 16 caractères, 32 bits = 8 caractères
    int     i;

    // Si la valeur est invalide (-1), écrire des espaces
    if (value == -1)
    {
        for (i = 0; i < width; i++)
            write(1, " ", 1);
        return;
    }

    // Initialiser le buffer avec des zéros
    for (i = 0; i < width; i++)
        buf[i] = '0';

    // Convertir la valeur en hexadécimal
    i = width - 1;
    while (value != 0 && i >= 0)
    {
        buf[i] = str[value % 16];
        value /= 16;
        i--;
    }

    // Écrire le buffer
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
