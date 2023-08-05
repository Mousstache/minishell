/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 22:46:31 by motroian          #+#    #+#             */
/*   Updated: 2023/08/05 23:12:29 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_var(t_data *env, int i)
{
	int		j;
	int		k;
	char	*str;

	j = 0;
	k = 0;
	while (ft_isalpha(env->env_copy[i][j]) || env->env_copy[i][j] == '_')
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

char	*strjoin_value_var(char *str, int j, t_data *env)
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

char	*ft_strjoin_btw_quote(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + count_quotes(s2) + 1));
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (j < count_quotes(s2))
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
	if (s1)
		free(s1);
	return (str);
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

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*res;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!res)
// 		return (NULL);
// 	while (s1 && s1[i])
// 	{
// 		res[i] = s1[i];
// 		i++;
// 	}
// 	while (s2 && s2[j])
// 		res[i++] = s2[j++];
// 	res[i] = 0;
// 	if (s1)
// 		free(s1);
// 	if (s2)
// 		free(s2);
// 	return (res);
// }
