/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 22:57:02 by motroian          #+#    #+#             */
/*   Updated: 2023/08/06 21:36:00 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_between_quotes(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	count_quotes(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != str[0])
		i++;
	if (str[i] == str[0])
		i++;
	return (i);
}

void	ft_expand_quotes(char **new, int *i, char *str, t_data *env)
{
	int	j;

	j = 0;
	while (1)
	{
		if (count_between_quotes(str + *i, '"') > count_between_quotes(str + *i,
																		'$'))
		{
			*new = ft_strjoin_quote(*new, str + *i, '$');
			*i += count_between_quotes(str + *i, '$');
		}
		else
		{
			*new = ft_strjoin_quote(*new, str + *i, '"');
			*i += count_between_quotes(str + *i, '"');
			break ;
		}
		if (str[*i] == '$')
		{
			(*i)++;
			printf("char = %c\n", str[*i]);
			j = check_var_exist(env->env_copy, str + *i);
			if (j >= 0)
				*new = strjoin_value_var(*new, j, env);
			*i += count_var_len(str + *i);
		}
	}
}

void	ft_expand_else(char **new, int *i, char *str)
{
	if (count_between_quotes(str + *i, '"') < count_between_quotes(str + *i,
			39))
	{
		if (count_between_quotes(str + *i, '"') < count_between_quotes(str + *i,
																		'$'))
		{
			*new = ft_strjoin_quote(*new, str + *i, '"');
			*i += count_between_quotes(str + *i, '"');
		}
		else
		{
			*new = ft_strjoin_quote(*new, str + *i, '$');
			*i += count_between_quotes(str + *i, '$');
		}
	}
	else if (count_between_quotes(str + *i, 39) < count_between_quotes(str + *i,
																		'$'))
	{
		*new = ft_strjoin_quote(*new, str + *i, 39);
		*i += count_between_quotes(str + *i, 39);
	}
	else
	{
		*new = ft_strjoin_quote(*new, str + *i, '$');
		*i += count_between_quotes(str + *i, '$');
	}
}

char	*ft_expand(char *str, t_data *env)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			j = check_var_exist(env->env_copy, str + i);
			if (j >= 0)
				new = strjoin_value_var(new, j, env);
			i += count_var_len(str + i);
		}
		else if (str[i] == 39)
		{
			new = ft_strjoin_btw_quote(new, str + i);
			i += count_quotes(str + i);
		}
		else if (str[i] == '"')
			ft_expand_quotes(&new, &i, str, env);
		else
			ft_expand_else(&new, &i, str);
	}
	return (new);
}
