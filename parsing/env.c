/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 22:57:02 by motroian          #+#    #+#             */
/*   Updated: 2023/08/03 23:03:39 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**ft_unset(char **env, char *variable)
{
	char	**new;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	new = malloc(sizeof(char *) * (count_string(env) + 1));
	if (!new)
		return (NULL);
	while (env[++i])
	{
		k = -1;
		if (!strncmp(env[i], variable, ft_strlen(variable)))
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

int	count_between_quotes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_strjoin_quote(char *s1, char *s2, char c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + count_between_quotes(s2, c)
				+ 2));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (j < count_between_quotes(s2, c))
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
	if (s1)
		free(s1);
	return (str);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (res);
}

char	*get_value_var(t_env *env, int i)
{
	int		j;
	int		k;
	char	*str;

	j = 0;
	k = 0;
	while (is_alpha(env->env_copy[i][j]) || env->env_copy[i][j] == '_')
		j++;
	if (env->env_copy[i][j] != '=')
		return (NULL);
	else
	{
		j++;
		if (!env->env_copy[i][j])
			return (NULL);
		while (env->env_copy[i][j + k])
			k++;
		str = malloc(sizeof(char) * (k + 2));
		k = 0;
		while (env->env_copy[i][j])
			str[k++] = env->env_copy[i][j++];
		str[k] = 0;
	}
	return (str);
}

int	check_var_exist(char **env, char *variable)
{
	int	i;

	i = 0;
	if (count_var_len(variable) < 1)
		return (-1);
	while (env[i])
	{
		if (strncmp(env[i], variable, count_var_len(variable)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*tab;

	i = 0;
	tab = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**add_variable(t_env *env)
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

char	*ft_strjoin_alphanum(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + count_var_len(s2) + 1));
	if (!res)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (j < count_var_len(s2))
	{
		res[i + j] = s2[j];
		j++;
	}
	if (s1)
		free(s1);
	res[i + j] = 0;
	return (res);
}

int	len_before_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '"')
		i++;
	return (i);
}

int	char_var_correct(char *str)
{
	int	i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (0);
	while (str && str[i])
	{
		if (!is_alphanum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*delete_quotes(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 39 || str[i] == '"')
			i++;
		else
			res[j++] = str[i++];
	}
	res[j] = 0;
	if (str)
		free(str);
	return (res);
}

char	*strjoin_value_var(char *str, int j, t_env *env)
{
	int		i;
	int		k;
	char	*res;
	char	*value;

	i = 0;
	k = 0;
	value = get_value_var(env, j);
	res = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(value) + 3));
	if (!res)
		return (NULL);
	while (str && str[k])
		res[i++] = str[k++];
	res[i++] = 39;
	k = 0;
	while (value && value[k])
		res[i++] = value[k++];
	res[i] = 39;
	res[i + 1] = 0;
	free(value);
	if (str)
		free(str);
	return (res);
}

char	*ft_expand(char *str, t_env *env)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			j = check_var_exist(env->env_copy, str + i);
			if (j >= 0)
				new = strjoin_value_var(new, j, env);
			i += count_var_len(str + i);
		}
		else
		{
			new = ft_strjoin_quote(new, str + i, '$');
			if (!new)
				return (NULL);
			i += count_between_quotes(str + i, '$');
		}
	}
	return (new);
}

int	is_not_var_char(char c)
{
	if (!is_alphanum(c) && c != '$' && c != '=' && c != '|' && c != ' '
		&& c != '"' && c != 39)
		return (1);
	return (0);
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

void	ft_export(t_env *env, char *str)
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
		env->var_value[j] = str[i];
		i++;
		j++;
	}
	env->var_value[j] = 0;
	// printf("yoyo\n");
	env->env_copy = add_variable(env);
}

char	**create_env(char **env)
{
	int		i;
	char	**str;

	i = 0;
	str = calloc(sizeof(char *), (count_string(env) + 1));
	if (!str)
		return (NULL);
	while (env[i])
	{
		str[i] = ft_strdup(env[i]);
		i++;
	}
	return (str);
}

void	print_double(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		printf("%s\n", str[i++]);
}

int	main(int argc, char **argv, char **env)
{
	// char **env2 = NULL;
	// // print_double(env);
	// env2 = create_env(env);
	// print_double(env2);
	// printf("nombre tab = %d\n", count_string(env2));
	// printf("-----------------------------------------------------");
	// printf("-----------------------------------------------------");
	// printf("-----------------------------------------------------");
	// env2 = ft_unset(env2, "lol");
	// printf("nombre tab = %d\n", count_string(env2));
	// print_double(env2);
	// free_all(env2);

	t_env envv;

	// envv = malloc(sizeof(t_env));
	// printf("reponse = %s\n", argv[1]);
	envv.var_name = NULL;
	envv.var_value = NULL;
	envv.env_copy = create_env(env);
	// add_var_name(&envv, "salut$VTE_VERSION='$VTE_VERSION$USER$caca'");
	// add_var_name(&envv, "lol=$PWD");
	// envv.env_copy = add_variable(&envv);
	// print_double(envv.env_copy);
	envv.env_copy = ft_unset(envv.env_copy, "USER");
	ft_export(&envv, "wesh=12");
	print_double(envv.env_copy);
	char *str = ft_expand("lscolors = $LSCOLORS none = $1234 none= $''yo system = $SYSTEMD_EXEC_PID none = $caca",
							&envv);
	str = delete_quotes(str);
	printf("%s\n", str);
	free_all(envv.env_copy);
	free(str);
	// free(envv.var_name);
	//     ft_export(&envv, "salut les mecs=12");
	//     print_double(envv.env_copy);
	//     free_all(envv.env_copy);
}