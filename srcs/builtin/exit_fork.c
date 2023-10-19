/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:01:10 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/29 22:26:11 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_error(char **arg)
{
	t_data		*data;
	long long	tmp;

	data = starton();
	tmp = ft_atoi_max(arg[0]);
	if (arg[1] && ft_is_num(arg[0]))
	{
		ft_printf("%s", "bash: exit: too many arguments\n");
		return (0);
	}
	else if (arg[0] && !ft_is_num(arg[0]))
	{
		printf("exit\n");
		ft_printf("bash: exit: %s: numeric argument required\n", arg[0]);
		free_arg(0, 3, 1, data->cmds->arg, data->tab, data->env_copy,
			&data->cmds->lst);
		exit((unsigned char)tmp);
	}
	free_arg(0, 3, 1, data->cmds->arg, data->tab, data->env_copy,
		&data->cmds->lst);
	exit((unsigned char)tmp);
}

int	exit_fork(char **arg, char **env)
{
	t_data	*data;

	(void)env;
	data = starton();
	if (!*arg || !arg[0])
	{
		free_arg(0, 3, 1, data->cmds->arg, data->tab, data->env_copy,
			&data->cmds->lst);
		exit(0);
	}
	if (arg[0] && !ft_strcmp(arg[0], "--"))
	{
		if (!arg[1])
		{
			printf("exit\n");
			free_arg(0, 3, 1, data->cmds->arg, data->tab, data->env_copy,
				&data->cmds->lst);
			exit(0);
		}
		else if (!exit_error(arg + 1))
			return (0);
	}
	exit_error(arg);
	return (0);
}
