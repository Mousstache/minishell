/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahouari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:37:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/09/18 20:44:46 by yahouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	into_while_main(t_data *data, char *input)
{
	input = posquote(input);
	negatif(input);
	if (!input)
		exit(1);
	if (here_doc(data, input))
		return (1);
	data->tab = ft_split(input, "|");
	data->nbcmd = ft_strlen_total(input, "|");
	free(input);
	if (init_struct(data, data->env_copy))
		return (1);
	ft_pipex(data, data->tab, &data->env_copy);
	free_docsmains(data->docs, data->nb_hd);
	ft_free_tab(data->tab);
	return (0);
}

int	empty_str(char *str)
{
	int	i;

	i = 0;
	while (str && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

char	*travailavecinput(char *input, t_data *data)
{
	positif(input);
	input = parse_input(input);
	input = posquote(input);
	input = ft_expandd(input, data);
	return (input);
}

int	while_main(t_data *data, char *input)
{
	while (1)
	{
		input = readline("minisheu> ");
		if (!input)
			break ;
		if (!*input)
			continue ;
		add_history(input);
		if (empty_str(input))
		{
			free(input);
			continue ;
		}
		if (negatif(input) && valid_syntax(input, data))
			continue ;
		input = travailavecinput(input, data);
		if (!*input)
		{
			free(input);
			continue ;
		}
		if (into_while_main(data, input))
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*input;

	input = NULL;
	data = starton();
	(void)argv;
	(void)argc;
	data->env_copy = create_env(env, 0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	while_main(data, input);
	ft_free_tab(data->env_copy);
	return (data->status);
}
