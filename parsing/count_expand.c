/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 01:43:37 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/12 03:36:58 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (count_squote(str, &i, &n))
			;
		else if (str[i] == '$' && str[i + 1])
		{
			i++;
			value = expand_ok(&str[i], env, &i);
			if (value)
				n += ft_strlen(value);
		}
		else
		{
			n++;
			i++;
		}
	}
	return (n);
}
