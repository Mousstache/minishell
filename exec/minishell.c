/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:14:30 by motroian          #+#    #+#             */
/*   Updated: 2023/08/06 21:36:54 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_data *data, t_cmd *cmd, char **env)
{
	int		i;
	int		j;
	char	*line;

	j = 1;
	i = -1;
	if (ft_strchr(cmd->cmd, '/'))
		execve(cmd->cmd, cmd->arg, env);
	else
	{
		data->path = path_finder(env);
		while (data->path[++i])
		{
			line = ft_strjoin(data->path[i], "/");
			line = ft_realloc(line, cmd->cmd);
			if (access(line, F_OK | X_OK) == 0)
				execve(line, cmd->arg, env);
			free(line);
		}
	}
	ft_printf("bash: %s: command not found\n", cmd->cmd);
	free_all(cmd->tab);
	free(cmd->arg);
	error_free_exit(data);
}

int		get_pipe(t_data *data, char *file)
{
	int	i;

	i = -1;
	while (++i < data->nbhere)
	{
		if (!ft_strcmp(file, data->here[i].delim))
			return (data->here[i].fd[0]);
	}
	return (-1);
}

void	forking(t_data *data, int i, t_cmd *cmd)
{
	if (i != data->nbcmd - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	if (i != 0)
		dup_close(data->prev_pipe, STDIN_FILENO);
	ft_close(data);
	openfiles(data, cmd);
}

void	parent(t_data *data, int i, char **av)
{
	t_cmd	cmd;

	signal(SIGINT, &ctrlc);
	// negatif(av[i]);
	cmd = parse(av[i]);
	forking(data, i, & cmd);
	if (!cmd.cmd)
		exit(0);
	if (!ex_builtin(cmd.arg, &data->envi))
		exec(data, & cmd, data->envi);
	free_all(cmd.tab);
	free(cmd.arg);
	error_free_exit(data);
}

int		iscmdbuiltin(char *str, t_data *data)
{
	data->onecmd = parse(str);
	if (!data->onecmd.cmd)
		return (0);
	if (is_builtin(data->onecmd.arg, data->envi))
		return (1);
	free_all(data->onecmd.tab);
	free(data->onecmd.arg);
	free(data->onecmd.files);
	free(data->onecmd.redir);
	return (0);
}

void	process(t_data *data, char **av)
{
	int	i;

	i = -1;
	if (data->nbcmd == 1 && iscmdbuiltin(data->tab[0], data))
	{
		printf("================================================\n");
		ex_builtin(data->onecmd.arg, &data->envi);
		free_all(data->onecmd.tab);
		free(data->onecmd.arg);
		free(data->onecmd.files);
		free(data->onecmd.redir);
		return ;
	}
	while (++i < data->nbcmd)
	{
		pipe(data->fd);
		signal(SIGINT, SIG_IGN);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			error_free_exit(data);
		else if (data->pid[i] == 0)
			parent(data, i, av);
		else
		{
			close(data->fd[1]);
			if (data->prev_pipe != -1)
				close(data->prev_pipe);
			data->prev_pipe = data->fd[0];
			signal(SIGQUIT, SIG_IGN);
		}
	}
	close(data->fd[0]);
	waiting(data);
	signal(SIGINT, &ctrlc);
}
