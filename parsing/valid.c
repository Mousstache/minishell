/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:41:40 by motroian          #+#    #+#             */
/*   Updated: 2023/08/07 22:30:57 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_norm2(int *i, char *str)
{
	if (((str[*i] == '<') && (str[*i + 1] == '<'))
		|| ((str[*i] == '>') && (str[*i + 1] == '>')))
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

int	syntax(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i + 1] == '\0')
			if (ft_strchr("><|", str[i]) || ((str[i] == '<')
					&& (str[i + 1] == '<')) || ((str[i] == '>')
					&& (str[i + 1] == '>')))
				return (1);
		if (ft_norm2(&i, str))
			return (1);
		if ((str[i] == '>') || (str[i] == '<') || (str[i] == '|'))
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '	'))
				i++;
			if (ft_strchr("><|", str[i]))
				return (1);
		}
	}
	return (0);
}

int	norme(int *bool_s, int *bool_d, char *str, int *i)
{
	if (((str[*i] == 39) && (*bool_s == 0))
		|| ((str[*i] == 34) && (*bool_d == 0)))
	{
		if (str[*i] == 39)
			*bool_s = 1;
		else
			*bool_d = 1;
		if (str[*i +1] == '\0')
			return (-1);
		else
			(*i) += 1;
	}
	return (1);
}

// int	quotes(char *str)
// {
// 	int	i;
// 	int	bool_s;
// 	int	bool_d;

// 	i = -1;
// 	bool_s = 0;
// 	bool_d = 0;
// 	while (str[++i])
// 	{
// 		if (norme(&bool_s, &bool_d, str, &i) < 0)
// 			break ;
// 		if (((str[i] == 39) && (bool_s == 1))
// 			|| ((str[i] == 34) && (bool_d == 1)))
// 		{
// 			if (str[i] == 39)
// 				bool_s = 0;
// 			else
// 				bool_d = 0;
// 		}
// 	}
// 	if ((bool_s == 0) && (bool_d == 0))
// 		return (0);
// 	else
// 		return (1);
// }

// char	*negatif(char *str)
// {
// 	int	i;
// 	int	bool_s;
// 	int	bool_d;

// 	i = -1;
// 	bool_s = 0;
// 	bool_d = 0;
// 	while (str[++i])
// 	{
// 		if (norme(&bool_s, &bool_d, str, &i) < 0)
// 			break ;
// 		if (((str[i] != 39) && (bool_s == 1))
// 			|| ((str[i] != 34) && (bool_d == 1)))
// 			str[i] *= -1;
// 		if (((str[i] == 39) && (bool_s == 1))
// 			|| ((str[i] == 34) && (bool_d == 1)))
// 		{
// 			if (str[i] == 39)
// 				bool_s = 0;
// 			else
// 				bool_d = 0;
// 		}
// 	}
// 	return (str);
// }

int	quotes(char *str)
{
	int i = 0;
	int quote = 0;

	char c;
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
			{
				if (str[i++] == c)
					quote++;
				else
					break ;
			}
		}
	}
	return (quote % 2);
}

char *negatif(char *str)
{
	int i = 0;
	int quote = 0;

	char c;
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
				str[i++] *= -1;
			while (str[i] && (str[i] != c))
			{
				if (str[i++] == c)
					quote++;
				else
					break ;
			}
		}
	}
	return (str);
}