/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:46:00 by motroian          #+#    #+#             */
/*   Updated: 2023/08/06 21:25:24 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **arg, char **env)
{
	(void)env;
	char	*cmd = arg[0];
	static char	*tab[8] = {"cd", "echo", "pwd", "exit", "unset", "export", "env", NULL};
	int i;

	i = -1;
	while (tab[++i])
	{
		printf("%s|%s\n", tab[i], cmd);
		if (!ft_strcmp(cmd ,tab[i]))
		{
			return (1);
		}
	}
	return (0);
	
}

void	ft_printtab(char **str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
}

typedef int (*func)(char ***, char **);

int	ex_builtin(char **arg, char ***env)
{
	static char	*tab[7] = {"cd", "echo", "pwd", "export", "unset", "env", NULL};
	static func fonction[6] = {ft_cd, ft_echo, ft_pwd, ft_export, ft_unset, ft_env};
	int i;

	i = -1;
	while (tab[++i])
	{
		if (!ft_strcmp(arg[0] ,tab[i]))
		{
			/*if(!ft_strcmp("env" ,tab[i]))
			{
				printf("ENV addr value: %p\n", *env);
				exit(0);
			}*/

			fonction[i](env, ++arg);
			return (1);
		}
	}

	return (0);
	
}
