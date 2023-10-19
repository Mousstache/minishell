/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:15:13 by motroian          #+#    #+#             */
/*   Updated: 2023/08/14 00:08:05 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_quotes(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 39 || str[i] == '"')
			i++;
		else
			res[j++] = str[i++];
	}
	res[j] = 0;
	str = res;
	return (str);
}

int	len_before_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '"')
		i++;
	return (i);
}

int	is_not_var_char(char c)
{
	if (!ft_isalnum(c) && c != '$' && c != '=' && c != '|' && c != ' '
		&& c != '"' && c != 39)
		return (1);
	return (0);
}

char	**create_env(char **env, int tofree)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_calloc(sizeof(char *), (count_string(env) + 1));
	if (!str)
		return (NULL);
	while (env[i])
	{
		str[i] = ft_strdup(env[i]);
		i++;
	}
	if (tofree)
		free_all(env);
	return (str);
}
