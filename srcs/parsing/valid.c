/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahouari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:41:40 by motroian          #+#    #+#             */
/*   Updated: 2023/10/13 19:57:13 by yahouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_norm2(int *i, char *str)
{
	if (((str[*i] == '<') && (str[*i + 1] == '<')) || ((str[*i] == '>')
			&& (str[*i + 1] == '>')))
	{
		(*i) += 2;
		if (str[*i] == '\0')
			return (1);
		while (str[*i] && (str[*i] == ' ' || str[*i] == '	'))
			(*i)++;
		if (ft_strchr("><|", str[*i]))
			return (1);
	}
	return (0);
}

int	ft_doublepipe(int *i, char *str)
{
	if (str[*i] == '|')
	{
		(*i) += 1;
		while (str[*i] && (str[*i] == ' ' || str[*i] == '	'))
			(*i)++;
		if (str[*i] == '|')
			return (1);
	}
	return (0);
}

int	syntax(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '	'))
		i++;
	if (s[i] == '|')
		return (13);
	while (s[i])
	{
		if (!s[i + 1] && (ft_strchr("><|", s[i]) || (!ft_strncmp(&s[i], "<<", 2)
					|| !ft_strncmp(&s[i], ">>", 2))))
			return (10);
		if (ft_norm2(&i, s) || ft_doublepipe(&i, s))
			return (2);
		if ((s[i] == '>') || (s[i] == '<'))
		{
			i++;
			while (s[i] && (s[i] == ' ' || s[i] == '	'))
				i++;
			if (ft_strchr("><|", s[i]))
				return (3);
		}
		i++;
	}
	return (0);
}

int	quotes(char *str)
{
	int		i;
	int		quote;
	char	c;

	i = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && str[i] != 39 && str[i] != 34)
			i++;
		if (str[i] && (str[i] == 39 || str[i] == 34))
		{
			c = str[i];
			if (str[i++] == c)
				quote++;
			while (str[i] && (str[i] != c))
				i++;
			if (str[i++] == c)
				quote++;
			else
				break ;
		}
	}
	return (quote % 2);
}

int	ft_norme(char *str, int *i, int c, int *quote)
{
	c = str[*i];
	if (str[(*i)++] == c)
		(*quote)++;
	return (c);
}
