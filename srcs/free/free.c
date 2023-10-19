/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahouari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:09:30 by maheraul          #+#    #+#             */
/*   Updated: 2023/10/13 19:56:32 by yahouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	free_docsmains(t_doc *doc, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		free(doc[i].del);
		close(doc[i].fd[0]);
	}
	if (n)
		free(doc);
}

void	*free_arg(int str, int tab, int lst, ...)
{
	va_list	arg;

	va_start(arg, lst);
	while (str > 0)
	{
		free((char *)va_arg(arg, char *));
		str--;
	}
	while (tab > 0)
	{
		ft_free_tab((char **)va_arg(arg, char **));
		tab--;
	}
	while (lst > 0)
	{
		ft_lst_clear((t_list **)va_arg(arg, t_list **));
		lst--;
	}
	return (va_end(arg), NULL);
}

void	*free_pipex(t_data *data)
{
	int	i;
	int	var;

	i = 0;
	var = 0;
	while (i < data->nbcmd)
	{
		waitpid(data->pid[i++], &data->status, 0);
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		if (data->status == 131 && !var++)
			ft_printf("Quit (core dumped)\n");
		if (data->status == 2)
			data->status = 130;
	}
	free(data->pid);
	close(data->fd[0]);
	return (NULL);
}

void	free_all(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
