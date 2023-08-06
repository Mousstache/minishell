/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:55:40 by motroian          #+#    #+#             */
/*   Updated: 2023/08/06 19:30:13 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_opt(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			i++;
			while (str[i])
			{
				if (str[i] != 'n')
					return (0);
				i++;
			}
			return (1);
		}
	}
	return (0);
}

int	ft_echo(char ***env, char **tab)
{
	int	i;
	int	verif;

	i = 0;
	verif = 0;
	(void)env;
	while (is_opt(tab[i]) == 1)
	{
		verif = 1;
		i++;
	}
	while (tab[i])
	{
		printf("%s", tab[i]);
		if ((tab[i + 1] != NULL))
			printf(" ");
		i++;
	}
	if (verif != 1)
		printf("\n");
	return (0);
}

int	ft_pwd(char ***env, char **tab)
{
	char	path[PATH_MAX];

	(void)env;
	(void)tab;
	if (getcwd(path, PATH_MAX) == NULL)
		return (printf("error\n"), 1);
	printf("%s\n", path);
	return (0);
}

// int	ft_cd(char ***env, char **tab)
// {
// 	char	*str;

// 	(void)env;
// 	if (!tab[0])
// 	{
// 		str = getenv("HOME");
// 		if (!str)
// 			return (perror(tab[0]), 1);
// 		chdir(str);
// 		return (0);
// 	}
// 	if (tab[1])
// 		return (fprintf(stderr, "trop d'arguments\n"), 1);
// 	if (chdir(tab[0]) == -1)
// 		return (perror(tab[0]), 1);
// 	return (0);
// }

int    ft_cd(char ***env, char **tab)
{
    (void)env;
    if (tab[0] && tab[1])
    {
        printf("bash: cd: too many arguments\n");
        return (1);
    }
    if (tab[0] && chdir(tab[0]) == -1)
    {
        perror("cd");
        return (1);
    }
    return (0);
}

int   ft_env(char ***env, char **str)
{
	(void)str;
	int i;
	int size;
	char	**tab;
	
	i = 0;
	tab = *env;
	size = count_string(tab);
	printf("size >>>>>>>>>>>>>>>>>>>>>>>>>>>>%d\n", size);
	while (i < size)
		ft_printf("%s\n", tab[i++]);
	return (0);
}

// int main(int ac, char **av, char **env)
// {
// 	static char *tab[3] = {"aa", NULL};
// 	// if (ac < 2)
// 		// return 1;
// 	// ft_echo(++av, env);
// 	ft_pwd(av, env);
// 	ft_cd(tab, env);
// 	// printf("%i %s\n", chdir("~/"), av[1]);
// 	ft_pwd(av, env);
// }