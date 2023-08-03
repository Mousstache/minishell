/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:14:30 by motroian          #+#    #+#             */
/*   Updated: 2023/08/03 22:24:26 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strtab(char *str, char c);

int	ft_nofork(t_data *data, t_cmd *cmd, char **env)
{
	free(data->pid);
	data->fddup[0] = dup(STDOUT_FILENO);
	data->fddup[1] = dup(STDIN_FILENO);
	if (!openfile(data, cmd))
	{
		ft_is_builtin(cmd, env);
		dupclose(data->fddup);
		return (0);
	}
	dupclose(data->fddup);
	return (0);
}

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
	cmd = parse(av[i]);
	forking(data, i, & cmd);
	if (!cmd.cmd)
		exit(0);
	if (!ex_builtin(cmd.arg, data->env))
		exec(data, & cmd, data->env);
	free_all(cmd.tab);
	free(cmd.arg);
	error_free_exit(data);
}

void	process(t_data *data, char **av)
{
	int	i;

	i = -1;
	if (data->nbcmd == 1 && get_cmd(data))
		return (ft_nofork(data, data->onecmd, env), NULL);
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
	(void)env;
	while (1)
	{
		input = readline("moussa> ");
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (quotes(input))
			(printf("ko\n"));
		else
			negatif(input);
		if (syntax(input))
			printf ("syntax error\n");
		negatif(input);
		printf("%d\n", quotes(input));
		printf("%s\n", input);
		printf("%s\n", syntax(input) == 1 ? "syntax error !" : "ok");
		input = addspace(input);
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
