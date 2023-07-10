/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:09:39 by motroian          #+#    #+#             */
/*   Updated: 2023/07/10 18:13:49 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	syntax(char *str)
{
	int i;

	i = -1;
	if (str[0] == '|')
		return (1);
	while (str[++i])
	{
		if (((str[i] == '<') && (str[i + 1] == '<')) || ((str[i] == '>') && (str[i + 1] == '>')))
		{
			i++;
			if (str[i + 1] == '\0')
				return (1);
			while (((str[i]) && (str[i] == ' ')) || (str[i] == '	'))
				i++;
			if ((str[i] == '<') || (str[i] == '>') || (str[i] == '|'))
				return (1);
		}
		if (str[i + 1] == '\0')
		{
			if ((str[i] == '<') || (str[i] == '>') || (str[i] == '|')
				|| ((str[i] == '<') && (str[i + 1] == '<')) || ((str[i] == '>') && (str[i + 1] == '>')))
				return (1);
		}
	}
	return (0);
}

int main (int ac, char **av)
{
	(void)ac;
	printf("%d\n", syntax(av[1]));
}