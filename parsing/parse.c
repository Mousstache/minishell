/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:56:41 by motroian          #+#    #+#             */
/*   Updated: 2023/07/31 22:36:34 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf ("nombres redir %d\n", p);
	cmd.cmd = cmd.arg[0];
	return (cmd);
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
