/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:55:03 by motroian          #+#    #+#             */
/*   Updated: 2023/08/30 19:29:31 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_is_heredoc(char *str, int *i, int *n)
{
	int	x;

	x = *i;
	if (str[x] && str[x + 1] && str[x] == '<' && str[x + 1] == '<')
	{
		(*i) += 2;
		(*n) += 2;
		while (str[(*i)] && str[(*i)] != ' ')
		{
			(*n)++;
			(*i)++;
		}
		while (str[(*i)] && str[(*i)] != ' ')
		{
			(*n)++;
			(*i)++;
		}
		return (1);
	}
	return (0);
}

int	count_squote(char *str, int *i, int *n)
{
	if (str[(*i)] == 39)
	{
		(*n)++;
		(*i)++;
		while (str[(*i)] && str[(*i)] != 39)
		{
			(*n)++;
			(*i)++;
		}
		(*n)++;
		(*i)++;
		return (1);
	}
	return (0);
}

int	count_expand(char *str, t_data *env)
{
	int		i;
	char	*value;
	int		n;

	i = 0;
	n = 0;
	while (str && str[i])
	{
		if (count_squote(str, &i, &n) || count_is_heredoc(str, &i, &n))
			continue ;
		else if (str[i] == '$' && str[i + 1])
		{
			i++;
			value = expand_ok(&str[i], env, &i);
			if (value)
			{
				n += ft_strlen(value);
				free(value);
			}
			continue ;
		}
		n++;
		i++;
	}
	return (n);
}
