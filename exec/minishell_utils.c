/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:39:02 by motroian          #+#    #+#             */
/*   Updated: 2023/07/31 22:56:31 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waiting(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbcmd)
		waitpid(data->pid[i], NULL, 0);
}

void	safe_close(int fd)
{
	if (fd != -1)
		close(fd);
	fd = -1;
}

void	error_free_exit(t_data *data)
{
	if (data->prev_pipe != -1)
		safe_close(data->prev_pipe);
	if (data->fd[0] != -1)
		safe_close(data->fd[0]);
	if (data->fd[1] != -1)
		safe_close(data->fd[1]);
	free_all(data->path);
	free_all(data->tab);
	free(data->pid);
	exit(EXIT_FAILURE);
}

char	**path_finder(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
			return (ft_split(&env[i][5], ':'));
		i++;
	}
	return (NULL);
}

void	dup_close(int fd, int fd2)
{
	dup2(fd, fd2);
	close(fd);
}
