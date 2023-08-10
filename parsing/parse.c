/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:56:41 by motroian          #+#    #+#             */
/*   Updated: 2023/08/07 22:16:13 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_compt(char **tab, t_cmd *cmd)
{
	int	i;
	int	k;
	int	p;

	i = -1;
	k = 0;
	p = 0;
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

void	printstruct(t_cmd *cmds)
{
	for (int i = 0; cmds->arg[i]; i++)
	{
		if (i == 0)
		{
			fprintf(stderr, "CMD = {%s}\n", cmds->arg[0]);
			continue ;
		}
		if (i == 1)
			fprintf(stderr, "ARGS =");
		fprintf(stderr, "[%s]", cmds->arg[i]);
	}
	fprintf(stderr, "\n");
	// ft_printlist(cmds->lst);
}

char *positif(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
	return (str);
}

t_cmd	parse(char *str)
{
	static t_cmd	cmd = {0};
	int				i;
	int				k;
	int				p;

	cmd.tab = ft_split(str, ' ');
	i = -1;
	k = 0;
	p = 0;
	ft_compt(cmd.tab, &cmd);
	while (cmd.tab[++i])
	{
		if (!isaredirection(cmd.tab[i]))
		{
			cmd.arg[k++] = positif(cmd.tab[i]);
			// cmd.arg[k++] = cmd.tab[i];
		}
		else
		{
			cmd.redir[p] = isaredirection(cmd.tab[i]);
			cmd.files[p++] = cmd.tab[++i];
		}
	}
	// for (int z = 0; cmd.arg[z]; z++)
		// negatif(cmd.arg[z]);
	cmd.cmd = cmd.arg[0];
	// printstruct(&cmd);
	return (cmd);
}

void	init(t_data *data)
{
	data->prev_pipe = -1;
	data->fd[0] = -1;
	data->fd[1] = -1;
	// data->path = path_finder(env);
	data->pid = malloc(sizeof(int) * data->nbcmd);
	if (!data->pid)
		exit (1);
}
