/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:10:24 by motroian          #+#    #+#             */
/*   Updated: 2023/05/18 17:55:56 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_new(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*ft_gnl(int fd, int boolean)
{
	char			*str;
	static char		*position;
	char			*tmp;
	char			*ret;
	int				reader;

	reader = 1;
	if (boolean)
		return (free(position), NULL);
	str = malloc(sizeof(char) * (1 + 1));
	if (!str)
		return (NULL);
	while (!ft_strchr(position, '\n') && reader > 0)
	{
		reader = read(fd, str, 1);
		if (reader == -1)
			return (free(str), NULL);
		tmp = position;
		str[reader] = '\0';
		position = ft_realloc(tmp, str);
	}
	ret = ft_substr(position, 0, ft_new(position) + 1);
	tmp = position;
	position = ft_substr(tmp, ft_new(tmp) + 1, (ft_strlen(tmp) - ft_new(tmp)));
	return (free(tmp), free(str), ret);
}

int	here_doc(t_data *data, char *delim)
{
	char	*line;

	data->here_doc = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0666);
	delim = ft_strjoin(delim, "\n");
	while (1)
	{
		line = ft_gnl(0, 0);
		if (!line || !*line)
			break ;
		if (!ft_strcmp(line, delim))
			break ;
		ft_putstr_fd(line, data->here_doc);
		free(line);
	}
	ft_gnl(1, 1);
	free(line);
	free(delim);
	data->infile = data->here_doc;
	close(data->here_doc);
	return (0);
}
