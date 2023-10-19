/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:51:52 by motroian          #+#    #+#             */
/*   Updated: 2023/08/29 22:33:10 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add2(char **env, char **tab, int *k)
{
	if ((*k) > -1)
		tab = malloc(sizeof(char *) * (count_string(env) + 1));
	else
		tab = malloc(sizeof(char *) * (count_string(env) + 2));
	return (tab);
}

char	**add_variable(t_data *env, char **envv)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = -1;
	j = 0;
	tab = NULL;
	k = check_var_exist(envv, env->var_name);
	if (!env->var_name)
		return (envv);
	tab = add2(envv, tab, &k);
	while (envv[++i])
	{
		if (k == i)
			tab[j++] = ft_strjoin(env->var_name, env->var_value);
		else
			tab[j++] = ft_strdup(envv[i]);
	}
	if (k == -1)
		tab[j++] = ft_strjoin(env->var_name, env->var_value);
	tab[j] = NULL;
	free_all(envv);
	return (tab);
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

int	norme_export(char **str, t_data *envv, char ***env, int res)
{
	int	k;

	k = -1;
	while (str[++k])
	{
		envv->var_name = get_name_var(str[k]);
		if (!char_var_correct(envv->var_name))
		{
			export_error(str[k], "not a valid identifier");
			res = 1;
		}
		else
		{
			envv->var_value = ft_strchr(str[k], '=');
			*env = add_variable(envv, *env);
		}
		free(envv->var_name);
	}
	return (res);
}

int	ft_export(char **str, char ***env)
{
	int		res;
	t_data	envv;

	if (!str[0])
		return (0);
	res = 0;
	ft_memset(&envv, 0, sizeof(t_data));
	res = norme_export(str, &envv, env, res);
	return (res);
}
