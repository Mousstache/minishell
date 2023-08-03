/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:25:28 by motroian          #+#    #+#             */
/*   Updated: 2023/08/04 00:06:59 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_syntax(char *input, t_env *envv, char **env)
{
	if (quotes(input))
		return (ft_printf("quote fail\n"), 1);
	if (syntax(input))
		return (ft_printf("syntax error\n"), 1);
	printf("%p\n", envv);
	envv->var_name = NULL;
	envv->var_value = NULL;
	envv->env_copy = create_env(env);
	ft_expand(input, envv);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*input;

	data = calloc(1, sizeof(t_data));
	if (ac != 1)
		return 1;
	data = starton();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	(void)av;
	(void)env;
	while (1)
	{
		input = readline("moussa> ");
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (valid_syntax(input, data->env, env))
			return (printf ("fuck\n"));
		input = addspace(input);
		data->nbcmd = ft_strtab(input, '|');
		if (here_doc(data, input))
			continue ;
		init(data, env);
		data->tab = ft_split(input, '|');
		process(data, data->tab);
		free_all(data->path);
		free_all(data->tab);
		free(data->pid);
		for (int i = 0; i < data->nbhere; i++)
			close(data->here[i].fd[0]);
		free_heredoc(data);
	}
}
