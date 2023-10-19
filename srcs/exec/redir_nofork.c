/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_nofork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:59:43 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/30 19:44:43 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_fd_nofork(t_data *data, t_cmd *cmd, char *file)
{
	(void)data;
	(void)cmd;
	ft_printf("bash: %s: ", file);
	perror("");
	data->status = 1;
	return (1);
}

int	file_open(int fd, t_list *tmp)
{
	if (tmp->type == 1)
		fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (tmp->type == 2)
		fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (tmp->type == 3)
		fd = open(tmp->file, O_RDONLY);
	else if (tmp->type == 4)
		fd = 0;
	return (fd);
}

int	openfiles_nofork(t_data *data, t_cmd *cmd)
{
	t_list	*tmp;
	int		fd;
	int		i;

	fd = -1;
	i = 0;
	tmp = cmd->lst;
	while (tmp)
	{
		fd = file_open(fd, tmp);
		if (fd == -1)
			return (invalid_fd_nofork(data, cmd, tmp->file));
		if (tmp->type == 1 || tmp->type == 2)
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
		if (tmp->type != 4)
			close(fd);
		tmp = tmp->next;
	}
	while (i < data->nb_hd)
		close(data->docs[i].fd[0]);
	return (0);
}
