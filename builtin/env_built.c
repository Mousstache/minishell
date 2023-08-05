/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:53:30 by motroian          #+#    #+#             */
/*   Updated: 2023/08/05 23:21:37 by motroian         ###   ########.fr       */
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
	int z = 0;
	new = ft_calloc(sizeof(char *), (count_string(*env) + 1));
	if (!new)
		return (-1);
	while (var[++z])
	{
		while (*env[++i])
		{
			k = -1;
			if (!strncmp(*env[i], var[z], ft_strlen(var[z])))
				i++;
			new[j] = ft_calloc(0, sizeof(char) * (ft_strlen(*env[i]) + 1));
			if (!new[j])
				return (free_all(new), -1);
			while (*env[i][++k])
				new[j][k] = *env[i][k];
			j++;
		}
	}
	free_all(*env);
	env = &new;
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

int ft_export(t_data *env, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	env->var_name = get_name_var(str);
	if (!char_var_correct(env->var_name))
	{
		export_error(str, "not a valid identifier");
		free(env->var_name);
		return ;
	}
	i += count_between_quotes(str, '=');
	env->var_value = malloc(sizeof(char) * (ft_strlen(str + i) + 1));
	while (str[i])
	{
		env->var_value[j++] = str[i++];
	}
	env->var_value[j] = 0;
	env->env_copy = add_variable(env);
    return (0);
}
