/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:39:02 by motroian          #+#    #+#             */
/*   Updated: 2023/08/07 22:24:39 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waiting(t_data *data)
{
	int	i;
	int	var;

	i = -1;
	var = 0;
	while (++i < data->nbcmd)
	{
		waitpid(data->pid[i], &data->status, 0);
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		if (data->status == 131 && !var++)
			ft_printf("Quit (core dumped)\n");
	}
	// fprintf(stderr, "STATUS = %i\n", data->status);
}

void	safe_close(int fd)
{
	if (fd != -1)
		close(fd);
	fd = -1;
}

void	error_free_exit(t_data *data, int status)
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
	exit(status);
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
