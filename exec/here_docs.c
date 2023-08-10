/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:02:25 by motroian          #+#    #+#             */
/*   Updated: 2023/08/07 19:31:12 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*delims(t_here *hd, char *str, int max)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < max)
	{
		while (ft_isspace(str[i]))
			i++;
		while (str[i] != '<')
			i++;
		if (str[++i] != '<')
			continue ;
		i++;
		while (ft_isspace(str[i]))
			i++;
		while (ft_isspace(str[i]))
			i++;
		hd[j].delim = getmot(&str[i]);
		pipe(hd[j].fd);
		i += ft_strlen(hd[j++].delim);
	}
	return (NULL);
}

static void	exit_hd(int sig)
{
	t_data	*data;
	int		i;

	data = starton();
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < data->nbhere)
		{
			close(data->here[i].fd[1]);
			close(data->here[i].fd[0]);
			if (data->here[i].delim != NULL)
				free(data->here[i].delim);
		}
		free(data->here);
		data->stop = true;
		exit(130);
	}
}

void	slash(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
	if (sig == SIGINT)
		exit(130);
}

void	ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	child_process_hd(t_data *data, t_here *here, char *input)
{
	char	*str;
	int		i;

	i = -1;
	signal(SIGINT, &exit_hd);
	while (++i < data->nbhere)
	{
		while (1)
		{
			str = readline("hd>");
			if (!str || !ft_strcmp(here[i].delim, str))
				break ;
			ft_putendl_fd(str, here[i].fd[1]);
			free(str);
		}
		close(here[i].fd[0]);
		close(here[i].fd[1]);
	}
	free(input);
	free_heredoc(data);
	exit(0);
}

bool	here_doc(t_data *data, char *str)
{
	int	i;
	int	pid;

	i = -1;
	data->nbhere = count_hd(str);
	if (!data->nbhere)
		return (false);
	data->here = ft_calloc(sizeof(t_here), data->nbhere);
	if (!data->here)
		return (true);
	delims(data->here, str, data->nbhere);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		child_process_hd(data, data->here, str);
	}
	else if (pid > 0)
	{
		while (++i < data->nbhere)
			close(data->here[i].fd[1]);
	}
	waitpid(pid, NULL, 0);
	signal(SIGINT, &ctrlc);
	return (data->stop);
}
