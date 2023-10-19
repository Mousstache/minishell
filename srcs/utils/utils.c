/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 01:27:25 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/30 19:33:06 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mgamiloueee(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_strchr("><|", str[i]))
			str[i] *= -1;
		i++;
	}
	return (str);
}

void	ft_strcat(char *dst, char *src, int *n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	*n += j;
	free(src);
}

int	alphanum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
			&& c <= 'Z') || c == '_')
		return (0);
	return (1);
}

// void	printtab(char **tab)
// {
// 	for (int i = 0; tab[i]; i++)
// 		fprintf(stderr, "[%i]{%s}\n", i, tab[i]);
// }

// void	printstruct(t_cmd *cmds)
// {
// 	for (int i = 0; cmds->arg[i]; i++)
// 	{
// 		if (i == 0)
// 		{
// 			fprintf(stderr, "CMD = {%s}\n", cmds->arg[0]);
// 			continue ;
// 		}
// 		if (i == 1)
// 			fprintf(stderr, "ARGS =");
// 		fprintf(stderr, "[%s]", cmds->arg[i]);
// 	}
// 	fprintf(stderr, "\n");
// 	ft_printlist(cmds->lst);
// }

void	ft_perror(char *file)
{
	ft_printf("bash: %s: ", file);
	perror("");
}

void	error_cmd(char *cmd)
{
	if (!cmd)
		ft_printf(" : command not found\n");
	else
		ft_printf("%s: command not found\n", cmd);
}
