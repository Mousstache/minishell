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
.:
.
..
d
.git
include
libft
libft.a
Makefile
minishell
out1
out2
outfile
srcs
test

./.git:
.
..
branches
config
description
HEAD
hooks
index
info
logs
objects
packed-refs
refs

./.git/branches:
.
..

./.git/hooks:
.
..
applypatch-msg.sample
commit-msg.sample
fsmonitor-watchman.sample
post-update.sample
pre-applypatch.sample
pre-commit.sample
pre-merge-commit.sample
prepare-commit-msg.sample
pre-push.sample
pre-rebase.sample
pre-receive.sample
push-to-checkout.sample
update.sample

./.git/info:
.
..
exclude

./.git/logs:
.
..
HEAD
refs

./.git/logs/refs:
.
..
heads
remotes

./.git/logs/refs/heads:
.
..
master

./.git/logs/refs/remotes:
.
..
origin

./.git/logs/refs/remotes/origin:
.
..
HEAD

./.git/objects:
.
..
info
pack

./.git/objects/info:
.
..

./.git/objects/pack:
.
..
pack-5b132ed975506e0f39b57764a82b2949b577b366.idx
pack-5b132ed975506e0f39b57764a82b2949b577b366.pack

./.git/refs:
.
..
heads
remotes
tags

./.git/refs/heads:
.
..
master

./.git/refs/remotes:
.
..
origin

./.git/refs/remotes/origin:
.
..
HEAD

./.git/refs/tags:
.
..

./include:
.
..
minishell.h

./libft:
.
..
ft_atoi.c
ft_atoi.o
ft_bzero.c
ft_bzero.o
ft_calloc.c
ft_calloc.o
ft_isalnum.c
ft_isalnum.o
ft_isalpha.c
ft_isalpha.o
ft_isascii.c
ft_isascii.o
ft_isdigit.c
ft_isdigit.o
ft_isprint.c
ft_isprint.o
ft_itoa.c
ft_itoa.o
ft_lstadd_front.c
ft_lstclear.c
ft_lstdelone.c
ft_lstiter.c
ft_lstlast.c
ft_lstmap.c
ft_lstsize.c
ft_memchr.c
ft_memchr.o
ft_memcmp.c
ft_memcmp.o
ft_memcpy.c
ft_memcpy.o
ft_memmove.c
ft_memmove.o
ft_memset.c
ft_memset.o
ft_printf.c
ft_printf.o
ft_printf_utils.c
ft_printf_utils.o
ft_putchar_fd.c
ft_putchar_fd.o
ft_putendl_fd.c
ft_putendl_fd.o
ft_putnbr_fd.c
ft_putnbr_fd.o
ft_putstr_e.c
ft_putstr_e.o
ft_putstr_fd.c
ft_putstr_fd.o
ft_realloc.c
ft_realloc.o
ft_split.c
ft_split.o
ft_strchr.c
ft_strchr.o
ft_strcmp.c
ft_strcmp.o
ft_strdup.c
ft_strdup.o
ft_striteri.c
ft_striteri.o
ft_strjoin.c
ft_strjoin.o
ft_strlcat.c
ft_strlcat.o
ft_strlcpy.c
ft_strlcpy.o
ft_strlen.c
ft_strlen.o
ft_strmapi.c
ft_strmapi.o
ft_strncmp.c
ft_strncmp.o
ft_strnstr.c
ft_strnstr.o
ft_strrchr.c
ft_strrchr.o
ft_strtrim.c
ft_strtrim.o
ft_substr.c
ft_substr.o
ft_tolower.c
ft_tolower.o
ft_toupper.c
ft_toupper.o
libft.h
Makefile

./srcs:
.
..
bonus_pipex.c
bonus_pipex.o
bonus_pipex_utils.c
bonus_pipex_utils.o
bonus_utils.c
bonus_utils.o
here_doc.c
main.c
main.o

./test:
.
..
a
b
moha
