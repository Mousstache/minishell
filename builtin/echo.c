/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:55:40 by motroian          #+#    #+#             */
/*   Updated: 2023/07/04 21:43:23 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	is_opt(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '-' && str[i + 1] == 'n')
			return (1);
	}
	return (0);
}

int	ft_echo(char **tab, char **env)
{
	int	i;

	i = -1;
	(void)env;
	while(tab[++i])
	{
		if ((is_opt(tab[i])))
		{
			i++;
		}
		printf("%s", tab[i]);
		if ((tab[i + 1] == NULL) && !(is_opt(tab[i])))
		{
			// printf("\n");
			break ;
		}
		else if ((tab[i + 1] == NULL) && (is_opt(tab[i])))
		{
			printf("\n");
			break ;
		}
		printf(" ");
	}
	// printf("\n");
}


int main(int ac, char **av, char **env)
{
	if (ac < 2)
		return 1;
	ft_echo(++av, env);
}