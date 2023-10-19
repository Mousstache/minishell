/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 20:38:49 by motroian          #+#    #+#             */
/*   Updated: 2023/08/30 21:21:32 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copyall(t_var *var, char *input, char *new, char c)
{
	new[var->j++] = input[var->i++];
	while (input[var->i] && input[var->i] != c)
		new[var->j++] = input[var->i++];
}
