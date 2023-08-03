/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:17:21 by motroian          #+#    #+#             */
/*   Updated: 2023/08/02 23:24:17 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_hd(char *str)
{
	int	nb;
	int	i;

	i = -1;
	nb = 0;
	while (str && str[++i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			nb++;
	}
	return (nb);
}

void	free_heredoc(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbhere)
		free(data->here[i].delim);
	if (data->nbhere)
	{
		free(data->here);
		data->here = NULL;
	}
}

int	lenmot(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

char	*getmot(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(lenmot(str) + 1, 1);
	if (!new)
		return (NULL);
	while (str[i] && !ft_isspace(str[i]))
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}
