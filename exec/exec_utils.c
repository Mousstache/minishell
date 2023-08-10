/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:00:32 by motroian          #+#    #+#             */
/*   Updated: 2023/08/07 19:29:37 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*starton(void)
{
	static t_data	data;

	return (&data);
}

int	isaredirection(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (2);
	if (!ft_strcmp(str, "<"))
		return (3);
	if (!ft_strcmp(str, "<<"))
		return (4);
	return (0);
}

void	ft_clean(t_cmd *cmd, t_data *data)
{
	int	i;

	i = -1;
	while(++i < data->nbhere)
		close(data->here[i].fd[0]);
	free_heredoc(data);
	free(cmd->files);
	free(cmd->redir);
}

void	openfiles(t_data *data, t_cmd *cmd)
{
	int	i;
	int	fd;

	i = -1;
	while (cmd->files[++i])
	{
		if (cmd->redir[i] == 1)
			fd = open(cmd->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (cmd->redir[i] == 2)
			fd = open(cmd->files[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (cmd->redir[i] == 3)
			fd = open(cmd->files[i], O_RDONLY , 0666);
		if (cmd->redir[i] == 4)
			fd = get_pipe(data, cmd->files[i]);
		if (fd == -1)
			error_free_exit(data, 1);
		if (cmd->redir[i] == 1 || cmd->redir[i] == 2)
			dup_close(fd, STDOUT_FILENO);
		else if (cmd->redir[i] == 3)
			dup_close(fd, STDIN_FILENO);
		else if (cmd->redir[i] == 4)
			dup2(fd, STDIN_FILENO);
	}
	ft_clean(cmd, data);
}
