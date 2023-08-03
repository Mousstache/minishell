/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:53:30 by motroian          #+#    #+#             */
/*   Updated: 2023/08/03 21:47:03 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **ft_unset(char **variable, char **env)
{
    char    **new;
    int        i;
    int        j;
    int        k;

    i = -1;
    j = 0;
    new = malloc(sizeof(char *) * (count_string(env) + 1));
    if (!new)
        return (NULL);
    while (env[++i])
    {
        k = -1;
        if (!strncmp(env[i], variable[0], ft_strlen(variable[0])))
            i++;
        new[j] = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
        if (!new[j])
            return (free_all(new), NULL);
        while (env[i][++k])
            new[j][k] = env[i][k];
        new[j][k] = 0;
        j++;
    }
    new[j] = NULL;
    return (free_all(env), new);
}

void    ft_env(char **str)
{
    int i;

    i = 0;
    while (str && str[i])
        ft_printf("%s\n", str[i++]);
}
