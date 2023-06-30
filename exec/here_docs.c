/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:02:25 by motroian          #+#    #+#             */
/*   Updated: 2023/06/30 20:02:46 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		count_hd(char *str)
{
	int nb;

	nb = 0;
	int i = -1;
	while (str && str[++i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			nb++;
	}
	return (nb);
}

void	free_heredoc(t_data *data)
{
	for (int i = 0; i < data->nbhere; i++)
		free(data->here[i].delim);
	if (data->nbhere)
	{
		free(data->here);
		data->here = NULL;
	}
}

// << hello asd sab ccb |B DF<D>S >FDF << world << c

int		lenmot(char *str)
{
	int i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

char	*getmot(char *str)
{
	char *new = ft_calloc(lenmot(str) + 1, 1);
	if (!new)
		return (NULL);
	int i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}

void	*delims(t_here *hd, char *str, int max)
{
	int i = 0;
	int j = 0;// cat << ok
	printf("str : %s\n", str);
	while (j < max)
	{
		while (ft_isspace(str[i]))
			i++;
		while (str[i] != '<') // && str[i + 1] != '<')
			i++;
		if (str[++i] != '<')
			continue ;
		i++;
		i++;
		while (ft_isspace(str[i]))
			i++;
		printf("boucle : %s\n", &str[i]);
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
			printf("JE FREE JE CLOSe\n");
		}
		free(data->here);
		printf("avant %i\n", data->stop);
		data->stop = true;
		printf("apres %i\n", data->stop);
		exit(130);
	}
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
	signal(SIGINT, &exit_hd);
	char *str;
	for (int i = 0; i < data->nbhere; i++)
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
	data->nbhere = count_hd(str);
	if (!data->nbhere)
		return (false);
	// printf("nb here = %i\n", data->nbhere);
	data->here = ft_calloc(sizeof(t_here), data->nbhere);
	if (!data->here)
		return (true);
	delims(data->here, str, data->nbhere);
	for (int i = 0; i < data->nbhere; i++)
		printf("%i->[%s]\n", i, data->here[i].delim);
	signal(SIGINT, SIG_IGN);
	int pid = fork();
	if (pid == 0)
	{
		child_process_hd(data, data->here, str);
	}
	else if (pid > 0)
	{
		for (int i = 0; i < data->nbhere; i++)
			close(data->here[i].fd[1]);
	}
	wait(NULL);
	signal(SIGINT, &ctrlc);
	printf("bool = %i\n", data->stop);
	return (data->stop);
}