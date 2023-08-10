/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:25:28 by motroian          #+#    #+#             */
/*   Updated: 2023/08/07 22:21:19 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_syntax(char **input, t_data *data)
{
	if (quotes(*input))
		return (ft_printf("quote fail\n"), free(*input), 1);
	if (syntax(*input))
		return (ft_printf("syntax error\n"), free(*input), 1);
	data->var_name = NULL;
	data->var_value = NULL;
	// printf("AVANT [%s]\n", *input);
	*input = ft_expand(*input, data);
	// printf("APRES [%s]\n", *input);
	return (0);
}



int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*input;

	if (ac != 1)
		return 1;
	data = starton();
	data->envi = create_env(env);
	data->env_copy = data->envi;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	(void)av;
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
		if (valid_syntax(&input, data))
			continue ;
		negatif(input);
		input = delete_quotes(input);
		// char s[2] = "\0";
		input = addspace(input);
		data->nbcmd = ft_strtab(input, '|');
		if (here_doc(data, input))
			continue ;
		init(data);
		data->tab = ft_split(input, '|');
		free(input);
		process(data, data->tab);
		free_all(data->path);
		free_all(data->tab);
		free(data->pid);
		for (int i = 0; i < data->nbhere; i++)
			close(data->here[i].fd[0]);
		free_heredoc(data);
	}
	free_all(data->env_copy);
}
