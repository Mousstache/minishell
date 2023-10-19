/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahouari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:36:11 by maheraul          #+#    #+#             */
/*   Updated: 2023/10/03 19:15:00 by yahouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i + 1] && str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] && str[i] != 'n')
			return (1);
		return (0);
	}
	return (1);
}

int	ft_echo(char **arg, char ***env)
{
	int	i;
	int	n;

	(void)env;
	i = 0;
	n = 0;
	if (arg[i])
	{
		while (arg[i] && !ft_check_n(arg[i]))
		{
			i++;
			n++;
		}
		while (arg[i])
		{
			write(1, arg[i], ft_strlen(arg[i]));
			if (arg[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}
