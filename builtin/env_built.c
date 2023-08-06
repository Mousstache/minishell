/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:53:30 by motroian          #+#    #+#             */
/*   Updated: 2023/08/06 21:15:27 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_unset(char ***env, char **var)
{
	char	**new;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	int z = -1;
	new = ft_calloc((count_string(*env) + 1), sizeof(char *));
	printf("%d\n", count_string(*env));
	if (!new)
		return (-1);
	while (var[++z])
	{
		printf("Value: %s\n" ,(*env)[++i]);
		while ((*env)[++i])
		{
			k = -1;
			if (!strncmp((*env)[i], var[z], ft_strlen(var[z])))
				i++;
			printf("Env[%d]: %s, var : %s \n",i,  (*env)[i], var[z]);
			if ((*env)[i])
			{
				new[j] = ft_calloc((ft_strlen((*env)[i]) + 1), sizeof(char));
				if (!new[j])
					return (free_all(new), -1);
				while ((*env)[i][++k])
					new[j][k] = (*env)[i][k];
			}
			j++;
		}
	}
	printf("Count string: %d\n", count_string(new));
	printf("Print the current env \n");
	ft_env(&new, NULL);
	free_all(*env);
	*env = new;
	return (0);
}
char	**add_variable(t_data *env)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = -1;
	j = 0;
	k = check_var_exist(env->env_copy, env->var_name);
	if (!env->var_name)
		return (env->env_copy);
	if (k > -1)
		tab = malloc(sizeof(char *) * (count_string(env->env_copy) + 1));
	else
		tab = malloc(sizeof(char *) * (count_string(env->env_copy) + 2));
	while (env->env_copy[++i])
	{
		if (k == i)
			tab[j++] = ft_strjoin(env->var_name, env->var_value);
		else
			tab[j++] = ft_strdup(env->env_copy[i]);
	}
	if (k == -1)
		tab[j++] = ft_strjoin(env->var_name, env->var_value);
	tab[j] = NULL;
	return (free_all(env->env_copy), tab);
}

char	*get_name_var(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i])
	{
		if (count_between_quotes(str + i, '=') > count_between_quotes(str + i,
																		' '))
			i += count_between_quotes(str + i, ' ') + 1;
		else
			break ;
	}
	new = malloc(sizeof(char) * (count_between_quotes(str + i, '=') + 1));
	if (!new)
		return (NULL);
	while (str[i] != 0 && str[i] != '=')
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = 0;
	return (new);
}

int	export_error(char *str, char *msg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_putchar_fd('"', 2);
	while (str && str[i])
		ft_putchar_fd(str[i++], 2);
	ft_putchar_fd('"', 2);
	ft_putchar_fd(' ', 2);
	while (msg[j])
		ft_putchar_fd(msg[j++], 2);
	ft_putchar_fd('\n', 2);
	return (i);
}

int    ft_export(char ***env, char **str)
{
    int    i;
    int    j;
    int k;
    int res;
	t_data	envv;

    i = 0;
    j = 0;
    k = -1;
    res = 0;
	memset(&envv, 0, sizeof(t_data));
	envv.env_copy = create_env(*env);
    while (str[++k])
    {
        envv.var_name = get_name_var(str[k]);
        if (!char_var_correct(envv.var_name))
        {
            export_error(*str, "not a valid identifier");
            free(envv.var_name);
            res = 1;
        }
        else
        {
            i += count_between_quotes(str[k], '=');
            envv.var_value = malloc(sizeof(char) * (ft_strlen(*str + i) + 1));
            while (str[k][i])
                envv.var_value[j++] = str[k][i++];
            envv.var_value[j] = 0;
			// free_all(*env);
			printf("\n\n\n\nNew env adress: %p\n\n\n\n", *env);
			*env = add_variable(&envv);
			ft_env(env, NULL);
			printf("\n\n\n\nNew env adress: %p\n\n\n\n", *env);
		}
    }
    return (res);
}
