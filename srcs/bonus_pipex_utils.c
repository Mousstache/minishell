/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:39:02 by motroian          #+#    #+#             */
/*   Updated: 2023/05/18 17:55:33 by motroian         ###   ########.fr       */
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

void	error_free_exit(t_data *data)
{
	if (data->here_doc != -42)
	{
		close(data->here_doc);
		unlink("here_doc");
	}
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (data->fd[1] != -1)
		close(data->fd[1]);
	free_all(data->path);
	free(data->pid);
	free(data);
	exit(EXIT_FAILURE);
}

char	**path_finder(char **env)
{
	int	i;

	i = 0;
	while (env[i])
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

void	message(t_data *data)
{
	perror("bash");
	error_free_exit(data);
}
