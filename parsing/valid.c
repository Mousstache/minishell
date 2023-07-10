/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:41:40 by motroian          #+#    #+#             */
/*   Updated: 2023/07/10 22:14:47 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

# define DQUOTE '\"'
# define SQUOTE '\''

int	quotes(char *str)
{
	int i = 0;
	int quote = 0;

	char c;
	while (str[i])
	{
		while (str[i] && str[i] != SQUOTE && str[i] != DQUOTE)
			i++;
		if (str[i] && (str[i] == SQUOTE || str[i] == DQUOTE))
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
		while (str[i] && str[i] != SQUOTE && str[i] != DQUOTE)
			i++;
		if (str[i] && (str[i] == SQUOTE || str[i] == DQUOTE))
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
int	syntax(char *str)
{
	int i;

	i = -1;
	if (str[0] == '|')
		return (1);
	while (str[++i])
	{
		if (str[i + 1] == '\0')
		{
			if ((str[i] == '<') || (str[i] == '>') || (str[i] == '|')
				|| ((str[i] == '<') && (str[i + 1] == '<')) || ((str[i] == '>') && (str[i + 1] == '>')))
				return (1);
		}
		if (((str[i] == '<') && (str[i + 1] == '<')) || ((str[i] == '>') && (str[i + 1] == '>')))
		{
			i+=2;
			if (str[i] == '\0')
				return (1);
			while (((str[i]) && (str[i] == ' ')) || (str[i] == '	'))
				i++;
			if ((str[i] == '<') || (str[i] == '>') || (str[i] == '|'))
				return (1);
		}
		if ((str[i] == '>') || (str[i] == '<') || (str[i] == '|'))
		{
			i++;
			while (((str[i]) && (str[i] == ' ')) || (str[i] == '	'))
				i++;
			if ((str[i] == '<') || (str[i] == '>') || (str[i] == '|'))
				return (1);
		}
	}
	return (0);
}

/*

Premire etape ; regles syntaxiques

La premiere chose a verifier ; quote si ouverte ou fermer
	Si fermer ok
	Si ouverte = erreur de syntaxe

 Petit exemple " <<< "
	Ici on sait que entre quote perte de valeur symbolique donc cest un caractere simple
	Le seul caractere qui garde sa valeur sy;bolique cest le $ dans un cas cest celui des doubles quotwe

	Ta deuxieme fonction mettre tt ce quil y a entre quote en negatif

	Puis fonction de parsing pour | et < 


// int	quotes(char *str)
// {
// 	int	i;
// 	int bool_s;
// 	int	bool_d;

// 	i = -1;
// 	bool_s = 0;
// 	bool_d = 0;
// 	while (str[++i])
// 	{
// 		if (((str[i] == 39) && (bool_s == 0)) || ((str[i] == 34) && (bool_d == 0)))
// 		{
// 			if (str[i] == 39)
// 				bool_s = 1;
// 			else
// 				bool_d = 1;
// 			if (str[i + 1] == '\0')
// 				break ;
// 			else
// 				i++;
// 		}
// 		if (((str[i] == 39) && (bool_s == 1)) || ((str[i] == 34) && (bool_d == 1)))
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
*/