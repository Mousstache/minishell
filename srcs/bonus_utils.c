/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:36:56 by motroian          #+#    #+#             */
/*   Updated: 2023/05/26 18:42:38 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_data *data)
{
	safe_close(data->fd[0]);
	safe_close(data->fd[1]);
}

// void	last_cmd(t_data *data, char **av)
// {
// 	if (data->here_doc != -42)
// 		data->outfile = open(av[data->nbcmd + 1],
// 				O_CREAT | O_APPEND | O_RDWR, 0666);
// 	else
// 		data->outfile = open(av[data->nbcmd + 2],
// 				O_CREAT | O_TRUNC | O_WRONLY, 0666);
// 	if (data->outfile == -1)
// 		message(data);
// 	dup_close(data->outfile, STDOUT_FILENO);
// }
