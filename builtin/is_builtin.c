/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:46:00 by motroian          #+#    #+#             */
/*   Updated: 2023/08/03 21:52:35 by motroian         ###   ########.fr       */
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
		if (!ft_strcmp(cmd , tab[i]))
			return (1);
	}
	return (0);
	
}

typedef int (*func)(char **, char **);

int	ex_builtin(char **arg, char **env)
{
	(void)env;
	char	*cmd = arg[0];
	static char	*tab[5] = {"cd", "echo", "pwd", NULL};
	static func fonction[4] = {ft_cd, ft_echo, ft_pwd};
	int i;

	i = -1;
	while (tab[++i])
	{
		if (!ft_strcmp(cmd , tab[i]))
		{
			fonction[i](++arg, env);
			// fprintf(stderr, "j'exec %s \n", tab[i]);
			return (1);
		}
	}
	return (0);
	
}
