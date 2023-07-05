/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:55:40 by motroian          #+#    #+#             */
/*   Updated: 2023/07/05 21:28:03 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>


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
			printf("option trouvee\n");
			return (1);
		}
	}
	return (0);
}

int	ft_echo(char **tab, char **env)
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
	while(tab[i])
	{
		printf("%s", tab[i]);
		if ((tab[i + 1] != NULL))
			printf(" ");
		i++;
	}
	if (verif != 1)
		printf("\n");
}

int	ft_pwd(char **tab, char **env)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	if (path == NULL)
		return (printf("error\n"), 1);
	printf("%s\n", path);
	return (0);
}

int	ft_cd(char **tab, char **env)
{
	char *str;

	if (tab[1])
		return (fprintf(stderr, "trop d'arguments\n"), 1);
	if (strcmp(tab[0], "~/"))
	{
		dprintf(2, "waf\n");
		str = getenv("HOME");
		if (!str)
			return (perror(tab[0]) , 1);
		chdir(str);
	}
	if (chdir(tab[0]) == -1)
		return (perror(tab[0]) , 1);
	// pas oublier de changer le $PWD de l'env
}

int main(int ac, char **av, char **env)
{
	// if (ac < 2)
		// return 1;
	// ft_echo(++av, env);
	ft_pwd(av, env);
	ft_cd(av + 1, env);
	// printf("%i %s\n", chdir("~/"), av[1]);
	ft_pwd(av, env);
}