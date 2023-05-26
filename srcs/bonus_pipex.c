/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:14:30 by motroian          #+#    #+#             */
/*   Updated: 2023/05/26 18:44:23 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strtab(char *str, char c);

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
		// data->path = path_finder(env);
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
	error_free_exit(data);
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
		if (fd == -1)
			error_free_exit(data);
		if (cmd->redir[i] == 1 || cmd->redir[i] == 2)
			dup_close(fd, STDOUT_FILENO);
		if (cmd->redir[i] == 3)
			dup_close(fd, STDIN_FILENO);
	}
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
// < Makefile
// ls -R
// ls > out -R
// sdfsdf
// {<}{infile1}{<}{infile2}{ls}{>}{outfile1}{-R}{>>}{append1}{-a}{<}{infile3}{-l}{>}{out}{-R}

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

t_cmd	parse(char *str)
{
	t_cmd	cmd;
	
	cmd.tab = ft_split(str, ' ');
	int i = -1;
	int k = 0;
	int p = 0;
	while (cmd.tab[++i])
	{
		if (!isaredirection(cmd.tab[i]))
		{
			cmd.arg[k++] = cmd.tab[i];
		}
		else
		{
			cmd.redir[p] = isaredirection(cmd.tab[i]);
			cmd.files[p++] = cmd.tab[++i];
		}
	}
	cmd.cmd = cmd.arg[0];
	cmd.arg[k] = NULL;
	cmd.files[p] = NULL;
	return (cmd);
}

void	process(t_data *data, char **av)
{
	t_cmd	cmd;
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
			cmd = parse(av[i]);
			forking(data, i, & cmd);
			exec(data, & cmd, data->env);
		}
		else
		{
			safe_close(data->fd[1]);
			if (data->prev_pipe != -1)
				safe_close(data->prev_pipe);
			data->prev_pipe = data->fd[0];
		}
	}
	safe_close(data->fd[0]);
	waiting(data);
}

void	init(t_data *data, char **env)
{
	data->env = env;
	data->prev_pipe = -1;
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->path = path_finder(env);
	data->pid = malloc(sizeof(int) * data->nbcmd);
	if (!data->pid)
		exit (1);
}

int	main(int ac, char **av, char **env)
{
	static t_data	data = {0};
	char	*input;
	if (ac != 1)
		return 1;
	(void)av;
	while (1)
	{
		input = readline("moussa>");
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		data.nbcmd = ft_strtab(input, '|');
		add_history(input);
		init(& data, env);
		data.tab = ft_split(input, '|');
		printf("%i\n", data.nbcmd);
		// (void)tab;
		process(& data, data.tab);
		// close(data.fd[0]);
		free_all(data.path);
		free_all(data.tab);
		free(data.pid);
		
	}
}
