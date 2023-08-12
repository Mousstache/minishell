/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:30:43 by motroian          #+#    #+#             */
/*   Updated: 2023/08/12 03:37:29 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_here
{
	char	*delim;
	int		fd[2];
}	t_here;

typedef struct s_env
{
	char	**env_copy;
	char	*var_name;
	char	*var_value;
}	t_env;

typedef struct s_cmd
{
	char	**arg;
	char	*cmd;
	int		*redir;
	char	**tab;
	char	**files;
}	t_cmd;

typedef struct s_data
{
	char	**env_copy;
	char	*var_name;
	char	*var_value;
	char	**path;
	char	**envi;
	char	**cmd;
	int		nbcmd;
	int		outfile;
	int		infile;
	int		prev_pipe;
	int		here_doc;
	int		*pid;
	char	**tab;
	int		fd[2];
	int		fddup[2];
	t_here	*here;
	t_cmd	cmds;
	// t_env	*env;
	int		nbhere;
	bool	stop;
	int		bool_s;
	int		bool_d;

	int		status;
	t_cmd	onecmd;
}	t_data;

// env
char	*positif(char *str);
char	*delete_quotes(char *str);
int		is_alphanum(char c);
int		count_string(char **env);
void	free_all(char **tab);
int		is_alpha(char c);
int		count_in_var(char *str);
int		ex_builtin(char **arg, char ***env);
char	*ft_expand(char *str, t_data *env);
int		count_quotes(char *str);
char	**create_env(char **env);
char	*ft_strjoin_quote(char *s1, char *s2, char c);
char	*ft_strjoin_alphanum(char *s1, char *s2);
char	*ft_strjoin_btw_quote(char *s1, char *s2);
char	*strjoin_value_var(char *str, int j, t_data *env);
char	*ft_strjoin2(char *s1, char *s2);
int		count_between_quotes(char *str, char c);
int		char_var_correct(char *str);
int		check_var_exist(char **env, char *variable);
int		count_var_len(char *str);

// builtin
int		ft_export(char ***env, char **str);
int		ft_unset(char ***env, char **variable);
int		ft_cd(char ***env, char **tab);
int		ft_echo(char ***env, char **tab);
int		ft_pwd(char ***env, char **tab);
int		ft_env(char ***env, char **str);

// here_doc
char	*getmot(char *str);
int		count_hd(char *str);
void	free_heredoc(t_data *data);
bool	here_doc(t_data *data, char *str);

//exec
int		ft_strtab(char *str, char c);
void	process(t_data *data, char **av);
void	free_all(char **tab);
char	*ft_gnl(int fd, int boolean);
void	slash(int sig);
void	error_free_exit(t_data *data, int status);
void	ft_printtab(char **tab);
char	**path_finder(char **env);
void	dup_close(int fd, int fd2);
int		isaredirection(char *str);
void	message(t_data *data);
void	waiting(t_data *data);
void	ft_close(t_data *data);
void	last_cmd(t_data *data, char **av);
t_data	*starton(void);
void	ctrlc(int sig);
int		quotes(char *str);
int		syntax(char *str);
char	*negatif(char *str);
char	*addspace(char *str);
int		syntax(char *str);
t_cmd	parse(char *str);
int		is_builtin(char **arg, char **env);
void	init(t_data *data);
void	openfiles(t_data *data, t_cmd *cmd);
int		get_pipe(t_data *data, char *file);
void	ft_compt(char **tab, t_cmd *cmd);


// expand
char	*ft_expandd(char *str, t_data *env);
int	count_expand(char *str, t_data *env);
int	copy_squote(char *str, char *new, int *i, int *n);
void	ft_strcat(char *dst, const char *src, int *n);
char	*expand_ok(char *str, t_data *env, int *clef);

#endif