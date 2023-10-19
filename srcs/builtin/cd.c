/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 02:56:31 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/30 21:16:47 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **arg, char ***env)
{
	char	*str;

	(void)env;
	if (arg[0] && arg[1])
	{
		ft_printf("bash: cd: too many arguments\n");
		return (1);
	}
	else if (!arg[0])
	{
		str = getenv("HOME");
		if (!str)
			return (ft_printf("bash: cd: HOME not set"), 1);
		return (chdir(str));
	}
	else if (arg[0] && chdir(arg[0]) == -1)
	{
		perror(arg[0]);
		return (1);
	}
	return (0);
}
