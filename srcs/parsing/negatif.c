/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negatif.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 20:28:36 by motroian          #+#    #+#             */
/*   Updated: 2023/08/30 20:29:15 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*negatif(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != 39 && str[i] != 34)
			i++;
		if (str[i] && (str[i] == 39 || str[i] == 34))
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
			{
				str[i] *= -1;
				i++;
			}
			if (str[i] == c)
				i++;
		}
	}
	return (str);
}
