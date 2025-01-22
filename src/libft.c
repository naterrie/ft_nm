/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:31:36 by naterrie          #+#    #+#             */
/*   Updated: 2025/01/22 13:32:26 by naterrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	int		i;

	i = 0;
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (0);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}
