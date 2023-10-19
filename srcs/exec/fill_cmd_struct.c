/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:40:06 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/30 21:22:02 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chevron_comp(char *str)
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

int	countarg(char **tab)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (tab[i])
	{
		if (chevron_comp(tab[i]))
		{
			i++;
			if (!tab[i])
				return (-1);
		}
		else
			size++;
		i++;
	}
	return (size);
}

t_list	*list_parse(char **input, t_list *lst, t_cmd *cmds)
{
	int	i;
	int	r;
	int	v;
	int	j;

	i = 0;
	v = 0;
	j = 0;
	while (input[i])
	{
		r = chevron_comp(input[i]);
		if (r)
		{
			ft_rediradd_back(&lst,
				ft_redirnew(positif(delete_quotes(((input[i + 1])))), r, v));
			if (r == 4)
				v++;
			i++;
		}
		else
			cmds->arg[j++] = positif(delete_quotes(input[i]));
		i++;
	}
	return (lst);
}

t_cmd	*parse_builtin(char *str)
{
	static t_cmd	cmds = {0};
	t_list			*lst;
	char			**input;
	int				len;

	lst = 0;
	input = ft_split(str, " 	");
	if (!input)
		return (NULL);
	len = countarg(input);
	if (len == -1)
		return (ft_freetab(input), &cmds);
	cmds.arg = ft_calloc(sizeof(char *), len + 1);
	if (!cmds.arg)
		return (ft_freetab(input), NULL);
	lst = list_parse(input, lst, &cmds);
	ft_freetab(input);
	cmds.cmd = cmds.arg[0];
	cmds.lst = lst;
	return (&cmds);
}

t_cmd	*parse(char *str)
{
	static t_cmd	cmds = {0};
	t_list			*lst;
	char			**input;
	int				len;

	lst = 0;
	input = ft_split(str, " 	");
	if (!input)
		return (NULL);
	len = countarg(input);
	if (len == -1)
		return (ft_freetab(input), ft_printf("ambigous redirect\n"),
			&cmds);
	cmds.arg = ft_calloc(sizeof(char *), len + 1);
	if (!cmds.arg)
		return (ft_freetab(input), NULL);
	lst = list_parse(input, lst, &cmds);
	ft_freetab(input);
	cmds.cmd = cmds.arg[0];
	cmds.lst = lst;
	return (&cmds);
}
