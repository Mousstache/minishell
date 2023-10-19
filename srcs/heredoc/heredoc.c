/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:15:00 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/30 22:40:40 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_hd(char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
			n++;
		i++;
	}
	return (n);
}

char	*next_word(char *str)
{
	int		i;
	char	*del;
	int		len;

	len = 0;
	i = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str && str[i] && str[i] != ' ' && str[i] != '\t')
	{
		i++;
		len++;
	}
	del = ft_calloc(sizeof(char), len + 1);
	if (!del)
		return (NULL);
	i = 0;
	len = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str && str[i] && str[i] != ' ' && str[i] != '\t')
		del[len++] = str[i++];
	return (del);
}

char	*del_is(t_doc *doc, char *str)
{
	int		i;
	int		n;
	t_data	*data;
	char	*tmp;

	n = 0;
	i = 0;
	data = starton();
	while (n < data->nb_hd)
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		{
			doc[n].index = n;
			tmp = next_word(&str[i + 2]);
			doc[n].del = positif(delete_quotes(tmp));
			free(tmp);
			pipe(doc[n].fd);
			n++;
		}
		i++;
	}
	return (0);
}

void	pid_null(int *i, t_doc *doc, char *str, t_data *data)
{
	while (*i < data->nb_hd)
	{
		close(doc[*i].fd[0]);
		child_hd(doc[*i].del, doc[*i].fd[1]);
		free(doc[*i].del);
		(*i)++;
	}
	free_arg(2, 1, 0, str, doc, data->env_copy);
	exit(0);
}

bool	here_doc(t_data *data, char *str)
{
	int		i;
	t_doc	*doc;
	pid_t	pid;

	i = 0;
	data->nb_hd = count_hd(str);
	if (data->nb_hd == 0)
		return (false);
	doc = ft_calloc(sizeof(t_doc), data->nb_hd);
	if (!doc)
		return (true);
	del_is(doc, str);
	data->docs = doc;
	data->str = str;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	i = 0;
	if (pid == 0)
		pid_null(&i, doc, str, data);
	else if (pid > 0)
		while (i < data->nb_hd)
			close(doc[i++].fd[1]);
	signal(SIGINT, &ctrlc);
	waitpid(pid, 0, 0);
	return (data->stop);
}
