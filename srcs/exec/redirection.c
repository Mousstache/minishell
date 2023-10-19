/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:49:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/29 20:27:25 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invalid_fd(t_data *data, t_cmd *cmd, char *file)
{
	close_heredocs(data->docs, data->nb_hd);
	ft_printf("bash: %s: ", file);
	perror("");
	free_arg(0, 3, 1, cmd->arg, data->tab, data->env_copy, &cmd->lst);
	if (data->previous != -1)
		close(data->previous);
	exit(1);
}

int	quelpipe(t_data *data, t_doc *doc, t_list *lst)
{
	int	i;

	i = -1;
	(void)lst;
	while (++i < data->nb_hd)
	{
		if (!ft_strcmp(lst->file, doc[i].del))
			return (doc[i].fd[0]);
	}
	return (-1);
}

void	close_heredocs(t_doc *doc, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		close(doc[i].fd[0]);
		free(doc[i++].del);
	}
	if (limit)
		free(doc);
}

void	openfiles(t_data *data, t_cmd *cmd)
{
	t_list	*tmp;
	int		fd;

	tmp = cmd->lst;
	while (tmp)
	{
		if (tmp->type == 1)
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (tmp->type == 2)
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (tmp->type == 3)
			fd = open(tmp->file, O_RDONLY);
		else if (tmp->type == 4)
			fd = quelpipe(data, data->docs, tmp);
		if (fd == -1)
			invalid_fd(data, cmd, tmp->file);
		if (tmp->type == 1 || tmp->type == 2)
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
		if (tmp->type != 4)
			close(fd);
		tmp = tmp->next;
	}
	close_heredocs(data->docs, data->nb_hd);
}

void	redirection(t_data *data, int index, t_cmd *cmd)
{
	if (index != data->nbcmd - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	if (index != 0)
	{
		dup2(data->previous, STDIN_FILENO);
		close(data->previous);
	}
	close(data->fd[0]);
	close(data->fd[1]);
	openfiles(data, cmd);
}
