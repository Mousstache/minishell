/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:14:30 by motroian          #+#    #+#             */
/*   Updated: 2023/05/18 17:55:41 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_data *data, char **av, char **env)
{
	int		i;
	int		j;
	char	*line;
	char	**cmd;

	j = 1;
	i = -1;
	cmd = ft_split(av[0], ' ');
	if (ft_strchr(av[0], '/'))
		execve(cmd[0], cmd, env);
	else
	{
		while (data->path[++i])
		{
			line = ft_strjoin(data->path[i], "/");
			line = ft_realloc(line, cmd[0]);
			if (access(line, F_OK | X_OK) == 0)
				execve(line, cmd, env);
			free(line);
		}
	}
	ft_printf("bash: %s: command not found\n", cmd[0]);
	free_all(cmd);
	error_free_exit(data);
}

void	forking(t_data *data, int i, char **av)
{
	if (i == 0)
	{
		if (data->here_doc != -42)
			data->infile = open("here_doc", O_RDONLY, 0666);
		else if (data->here_doc == -42)
			data->infile = open(av[i + 1], O_RDONLY);
		if (data->infile == -1)
			message(data);
		dup_close(data->infile, STDIN_FILENO);
	}
	else if (i == data->nbcmd - 1)
		last_cmd(data, av);
	if (i != data->nbcmd - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	if (i != 0)
		dup_close(data->prev_pipe, STDIN_FILENO);
	ft_close(data);
}

void	process(t_data *data, char **av)
{
	int	i;

	i = -1;
	while (++i < data->nbcmd)
	{
		pipe(data->fd);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			error_free_exit(data);
		else if (data->pid[i] == 0)
		{
			forking(data, i, av);
			if (data->here_doc != -42)
				exec(data, av + i + 1, data->env);
			else
				exec(data, av + i + 2, data->env);
		}
		close(data->fd[1]);
		if (data->prev_pipe != -1)
			close(data->prev_pipe);
		data->prev_pipe = data->fd[0];
	}
	close(data->prev_pipe);
	waiting(data);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (ac < 5)
		return (ft_printf("Pas assez d'arguments\n"), free(data), 0);
	data->here_doc = -42;
	if (!ft_strcmp(av[1], "here_doc"))
	{
		here_doc(data, av[2]);
		av = av + 2;
	}
	if (data->here_doc != -42)
		data->nbcmd = ac - 4;
	else
		data->nbcmd = ac - 3;
	data->pid = malloc(sizeof(int) * data->nbcmd);
	if (!data->pid)
		return (0);
	data->prev_pipe = -1;
	data->path = path_finder(env);
	data->fd[0] = -1;
	process(data, av);
	error_free_exit(data);
}
