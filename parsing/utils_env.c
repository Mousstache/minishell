/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:46:55 by motroian          #+#    #+#             */
/*   Updated: 2023/08/05 22:48:04 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_string(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		i++;
	}
	return (i);
}

int	count_in_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '>' && str[i] != '|' && str[i] != ' ')
		i++;
	return (i);
}

int	count_var_len(char *str)
{
	int i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

int	char_var_correct(char *str)
{
	int	i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (0);
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_var_exist(char **env, char *variable)
{
	int	i;

	i = 0;
	if (count_var_len(variable) < 1)
		return (-1);
	while (env[i])
	{
		if (strncmp(env[i], variable, count_var_len(variable)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
