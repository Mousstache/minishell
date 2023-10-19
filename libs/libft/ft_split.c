/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:33:31 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/11 22:25:07 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_freetab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	*ft_strndup(char const *src, int start, int end)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (end - start + 1));
	if (dest == NULL)
		return (NULL);
	while (i < end)
	{
		while (i < start)
			i++;
		while (i < end)
		{
			dest[j] = src[i];
			i++;
			j++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

int	ft_strlen_total(char const *str, char *sep)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (str[i])
	{
		while (ft_strchr(sep, str[i]) && str[i])
			i++;
		if (str[i] == '\0')
			break ;
		total++;
		while (!ft_strchr(sep, str[i]) && str[i])
			i++;
	}
	return (total);
}

char	**ft_split(char const *s, char *str)
{
	int		i;
	int		start;
	int		total;
	char	**tab;

	i = 0;
	total = 0;
	tab = malloc(sizeof(*tab) * (ft_strlen_total(s, str) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		while (ft_strchr(str, s[i]) && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (!ft_strchr(str, s[i]) && s[i])
			i++;
		tab[total++] = ft_strndup(s, start, i);
		if (!tab)
			return (ft_freetab(tab));
	}
	tab[total] = 0;
	return (tab);
}
