/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:35:08 by motroian          #+#    #+#             */
/*   Updated: 2023/08/05 18:44:40 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nofork(t_data *data, t_cmd *cmd, char **env)
{
	free(data->pid);
	data->fddup[0] = dup(STDOUT_FILENO);
	data->fddup[1] = dup(STDIN_FILENO);
	if (!openfile(data, cmd))
	{
		ft_is_builtin(cmd, env);
		dupclose(data->fddup);
		return (0);
	}
	dupclose(data->fddup);
	return (0);
}
