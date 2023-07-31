/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:53:30 by motroian          #+#    #+#             */
/*   Updated: 2023/07/31 22:36:20 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_unset(char **env, char *variable)
{
    char **new;
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    new = malloc(sizeof(char *) * (count_string(env) + 1));
    if (!new)
        return (NULL);
    while (env[i])
    {
        k = 0;
        if (!strncmp(env[i], variable, ft_strlen(variable)))
            i++;
        new[j] = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
        if (!new[j])
            return(free_all(new), NULL);
        while(env[i][k])
        {
            new[j][k] = env[i][k];
            k++;
        }    
        new[j][k] = 0;
        i++;
        j++;
    }
    new[j] = NULL;
    free_all(env);
    return(new);
}
void    ft_env(char **str)
{
    int i;

    i = 0;
    while (str && str[i])
        ft_printf("%s\n", str[i++]);
}
