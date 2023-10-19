/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:40:18 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/30 22:52:35 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dupclose(int fd[2])
{
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]);
	dup2(fd[1], STDIN_FILENO);
	close(fd[1]);
}

int	ft_nofork(t_data *data, t_cmd *cmd, char ***env)
{
	int	i;

	i = 0;
	free(data->pid);
	data->fddup[0] = dup(STDOUT_FILENO);
	data->fddup[1] = dup(STDIN_FILENO);
	if (!openfiles_nofork(data, cmd))
	{
		while (cmd->arg[i])
			positif(cmd->arg[i++]);
		data->status = ft_is_builtin(cmd, env);
	}
	free_arg(0, 1, 1, data->onecmd->arg, &data->onecmd->lst);
	dupclose(data->fddup);
	return (0);
}

void	ft_enfant(t_data *data, char **argv, int i, char ***env)
{
	t_cmd	*cmd;

	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, &slash);
	signal(SIGINT, &slash);
	cmd = NULL;
	free(data->pid);
	cmd = parse(argv[i]);
	data->cmds = cmd;
	if (cmd == NULL)
	{
		close_heredocs(data->docs, data->nb_hd);
		free_arg(0, 2, 1, cmd->arg, data->tab, &cmd->lst);
		exit(1);
	}
	redirection(data, i, cmd);
	if (cmd->cmd && ft_is_builtin_vrmnt(cmd->cmd))
		data->status = ft_is_builtin(cmd, env);
	else if (cmd->cmd)
	{
		execute(data, cmd, env);
		data->status = 127;
	}
	free_arg(0, 3, 1, data->env_copy, cmd->arg, data->tab, &cmd->lst);
	exit(data->status);
}

void	ft_parent(t_data *data, int i)
{
	close(data->fd[1]);
	if (i != 0)
		close(data->previous);
	data->previous = data->fd[0];
	signal(SIGQUIT, SIG_IGN);
}

void	*ft_pipex(t_data *data, char **argv, char ***env)
{
	int	i;

	i = -1;
	if (data->nbcmd == 1 && get_cmd(data))
		return (ft_nofork(data, data->onecmd, env), NULL);
	while (++i < data->nbcmd)
	{
		if (pipe(data->fd) == -1)
			return (write(2, "pipe failed\n", 13), NULL);
		signal(SIGINT, SIG_IGN);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			ft_enfant(data, argv, i, env);
		else if (data->pid[i] > 0)
			ft_parent(data, i);
	}
	return (free_pipex(data), signal(SIGINT, &ctrlc), NULL);
}
