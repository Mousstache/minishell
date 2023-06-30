/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addspace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:46:47 by motroian          #+#    #+#             */
/*   Updated: 2023/06/30 21:02:14 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_plus(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if ((str[i] == '|') || (str[i] == '<') || (str[i] == '>'))
			len+=2;
		else if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
		{
			len++;
			i++;
		}
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
		if ((str[i] == '|') || (str[i] == '<') || (str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>') || (str[i] == '>' && str[i + 1] == '>'))
		{
			// if (str[i - 1] != ' ')
			// {
				// final[j] = ' ';
				// j++;
			// }
			if (str[i + 1] != ' ')
			{
				final[j] = ' ';
				j++;
			}
		}
		else if ((str[i] == '<' && str[i + 1] == '<') ||  (str[i] == '>' && str[i + 1] == '>'))
		{
			// if (str[i - 1] != ' ')
			// {
				// final[j] = ' ';
				// j++;
			// }
			if (str[i + 2] != ' ')
			{
				final[j] = ' ';
				j++;
			}
		}
		final[j++] = str[i];
	}
	final[j] = 0;
	// printf("APRES {%s} %i | %zu\n", final, ft_plus(str), ft_strlen(final));
	printf("%d\n", ft_plus(str));
	free(str);
	return (final);
}
