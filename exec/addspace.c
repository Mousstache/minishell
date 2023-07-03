/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addspace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:46:47 by motroian          #+#    #+#             */
/*   Updated: 2023/07/03 20:14:37 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// char	*ft_clear(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*fin;

// 	i = -1;
// 	j = 0;
// 	fin = malloc(sizeof(char) * ft_strlen(str));
// 	while(str[++i])
// 	{
// 		if ((str[i] == ' ') && (str[i + 1] == ' '))
// 		{
// 			i++;
// 			while (str[i] == ' ')
// 				i++;
// 		}
// 		fin[j++] = str[i];
// 	}
// 	fin[j] = 0;
// 	return (fin);
// }

int	ft_plus(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
		{
			len+=4;
			i++;
		}
		else if ((str[i] == '|') || (str[i] == '<') || (str[i] == '>'))
			len+=3;
		else
			len++;
	}
	return (len);
}

char *addspace(char *str)
{
	char	*final;
	int		i;
	int		j;
 
	i = -1;
	j = 0;
	printf("AVANT [%s]\n", str);
	final = malloc(sizeof(char) * (ft_plus(str) + 1));
	while(str[++i])
	{
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
		{
			final[j++] = ' ';
			final[j++] = str[i++];
			final[j++] = str[i];
			final[j++] = ' ';
		}
		else if ((str[i] == '|') || (str[i] == '<') || (str[i] == '>'))
		{
			final[j++] = ' ';
			final[j++] = str[i];
			final[j++] = ' ';
		}
		else
			final[j++] = str[i];
	}
	final[j] = 0;
	printf("APRES {%s} %i | %zu\n", final, ft_plus(str), ft_strlen(final));
	printf("%d\n", ft_plus(str));
	free(str);
	// final = ft_clear(final);
	return (final);
}
