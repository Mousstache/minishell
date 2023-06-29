/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:14:30 by motroian          #+#    #+#             */
/*   Updated: 2023/06/26 23:29:01 by motroian         ###   ########.fr       */
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
	for (int i = 0; i < data->nbhere; i++)
	{
		fprintf(stderr, "{%s} [%s]\n", file, data->here[i].delim);
		if (!ft_strcmp(file, data->here[i].delim))
			return (data->here[i].fd[0]);
	}
	return (-1);
}

void	openfiles(t_data *data, t_cmd *cmd)
{
	int	i;
	int	fd;

	i = -1;
	while (cmd->files[++i])
	{
		// printf("[[[%s]]]->{%i}\n", cmd->files[i], cmd->redir[i]);
		if (cmd->redir[i] == 1)
			fd = open(cmd->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (cmd->redir[i] == 2)
			fd = open(cmd->files[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (cmd->redir[i] == 3)
			fd = open(cmd->files[i], O_RDONLY , 0666);
		if (cmd->redir[i] == 4)
			fd = get_pipe(data, cmd->files[i]);
		if (fd == -1)
			error_free_exit(data);
		if (cmd->redir[i] == 1 || cmd->redir[i] == 2)
			dup_close(fd, STDOUT_FILENO);
		else if (cmd->redir[i] == 3)
			dup_close(fd, STDIN_FILENO);
		else if (cmd->redir[i] == 4)
			dup2(fd, STDIN_FILENO);
	}
	for (int i = 0; i < data->nbhere; i++)
		close(data->here[i].fd[0]);
	free_heredoc(data);
	free(cmd->files);
	free(cmd->redir);
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

void	ft_compt(char **tab, t_cmd *cmd)
{
	int i = -1;
	int k = 0;
	int p = 0;

	while (tab[++i])
	{
		if (!isaredirection(tab[i]))
			k++;
		else
			p++;
	}
	cmd->arg = calloc(sizeof(char *), k + 1);
	cmd->files = calloc(sizeof(char *), p + 1);
	cmd->redir = calloc(sizeof(int), p + 1);
}

t_cmd	parse(char *str)
{
	static t_cmd	cmd = {0};
	
	cmd.tab = ft_split(str, ' ');
	int i = -1;
	int k = 0;
	int p = 0;
	ft_compt(cmd.tab, &cmd);
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
		signal(SIGINT, SIG_IGN);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			error_free_exit(data);
		else if (data->pid[i] == 0)
		{
			signal(SIGINT, &ctrlc);
			cmd = parse(av[i]);
			forking(data, i, & cmd);
			if (!cmd.cmd)
				exit(0) ;
			exec(data, & cmd, data->env);
		}
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

void	init(t_data *data, char **env)
{
	data->env = env;
	data->prev_pipe = -1;
	data->fd[0] = -1;
	data->fd[1] = -1;
	// data->path = path_finder(env);
	data->pid = malloc(sizeof(int) * data->nbcmd);
	if (!data->pid)
		exit (1);
}
t_data	*starton(void)
{
	static t_data	data;

	return (&data);
}
// echo $USER
// calcule de la longeur de la nouvelle string 
// calloc
// remplissage

char *catch_expand(char *str)
{
	int		i;
	char	*env_var;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (!ft_isspace(str[i]))
				i++;
		}
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*input;
	if (ac != 1)
		return 1;
	data = starton();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
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
		add_history(input);
		data->nbcmd = ft_strtab(input, '|');
		if (here_doc(data, input))
			continue ;
		init(data, env);
		data->tab = ft_split(input, '|');
		process(data, data->tab);
		free_all(data->path);
		free_all(data->tab);
		free(data->pid);
		for (int i = 0; i < data->nbhere; i++)
			close(data->here[i].fd[0]);
		free_heredoc(data);
	}
}
