/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:25:39 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/30 21:03:34 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# define LL_MAX 9223372036854775807UL
# define LL_MIN -9223372036854775807

typedef struct t_doc
{
	char			*del;
	int				fd[2];
	int				index;
}					t_doc;

typedef struct s_env
{
	char			**env_copy;
	char			*var_name;
	char			*var_value;
}					t_env;

typedef struct t_list
{
	char			*file;
	int				type;
	int				index;
	struct t_list	*next;
}					t_list;

typedef struct t_cmd
{
	t_list			*lst;
	char			**arg;
	char			*cmd;
}					t_cmd;

typedef struct t_data
{
	char			fakeitoa[5];
	int				nbcmd;
	int				status;
	char			**path;
	char			**tab;
	int				*pid;
	int				fork;
	int				previous;
	int				fd[2];
	int				fddup[2];
	bool			stop;
	char			**env;
	t_cmd			*onecmd;
	t_cmd			*cmds;
	int				nb_hd;
	t_doc			*docs;
	char			**env_copy;
	char			*var_name;
	char			*var_value;
	char			*str;
}					t_data;

typedef struct t_var
{
	int				i;
	int				j;
	int				n;
	int				d;
	int				len;
}					t_var;

typedef int			(*t_builtin)(char **arg, char ***env);

t_data				*starton(void);
int					init_struct(t_data *data, char **env);
t_cmd				*parse_builtin(char *str);
int					ft_strlen_total(char const *str, char *sep);
void				copyall(t_var *var, char *input, char *new, char c);

//utils
void				printtab(char **tab);
void				printstruct(t_cmd *cmds);
void				error_cmd(char *cmd);
int					alphanum(char c);
void				ft_strcat(char *dst, char *src, int *n);
char				*mgamiloueee(char *str);
//main.c
char				**path_recup(char **env);
//pipex
char				*write_path(char *cmd, t_data *data);
void				ft_parent(t_data *data, int i);
void				*ft_pipex(t_data *data, char **argv, char ***env);
//exec
char				*write_path(char *cmd, t_data *data);
void				*execute(t_data *data, t_cmd *cmd, char ***env);
int					get_cmd(t_data *data);
//redirection
void				redirection(t_data *data, int index, t_cmd *cmd);
void				invalid_fd(t_data *data, t_cmd *cmd, char *file);
void				openfiles(t_data *data, t_cmd *cmd);
void				close_heredocs(t_doc *doc, int limit);
int					quelpipe(t_data *data, t_doc *doc, t_list *lst);
// expand
int					count_expand(char *str, t_data *env);
char				*ft_expandd(char *str, t_data *env);
char				*expand_ok(char *str, t_data *env, int *clef);
//parse input
void				*parse_input(char *input);
//parse
int					ft_is_num(char *str);
char				*positif(char *str);
//fill_cmd_struct.c
int					chevron_comp(char *str);
int					countarg(char **tab);
t_cmd				*parse(char *str);
//lst.c
t_list				*ft_redirnew(char *file, int type, int index);
void				ft_rediradd_back(t_list **lst, t_list *new);
void				ft_lst_clear(t_list **lst);
void				ft_printlist(t_list *list);
//builtin
int					ft_is_builtin(t_cmd *cmd, char ***env);
int					ft_is_builtin_vrmnt(char *str);
int					ft_exit(char **arg, char ***env);
//echo.c
int					ft_echo(char **arg, char ***env);
//pwd.c
int					ft_pwd(char **arg, char ***env);
//cd.c
int					ft_cd(char **arg, char ***env);
//env.c
int					char_var_correct(char *str);
int					ft_export(char **str, char ***env);
int					ft_env(char **arg, char ***env);
int					ft_unset(char **var, char ***env);
//redirnofork
int					openfiles_nofork(t_data *data, t_cmd *cmd);
int					invalid_fd_nofork(t_data *data, t_cmd *cmd, char *file);
//free.c
void				*free_arg(int str, int tab, int lst, ...);
void				free_all(char **tab);
void				*free_pipex(t_data *data);
void				free_docsmains(t_doc *doc, int n);
void				*ft_free_tab(char **tab);
//heredoc
void				child_hd(char *del, int fd1);
bool				here_doc(t_data *data, char *str);
//exit
int					exit_one(char **arg);
int					ft_exit_error(char **arg);
long long			ft_atoi_max(char *str);
int					ft_is_num(char *str);
//exit fork
int					exit_fork(char **arg, char **env);
int					exit_error(char **arg);
void				dupclose(int fd[2]);
//syntac
int					posquote_two(char *input, int nb, int nb1, int i);
int					valid_syntax(char *input, t_data *data);
char				*posquote(char *input);
// signaux
void				ctrlc(int sig);
void				slash(int sig);

/********************************/

char				*ft_strjoin_quote(char *s1, char *s2, char c);
char				*strjoin_value_var(char *str, int j, t_data *env);
char				*get_value_var(t_data *env, int i);
char				*ft_strjoin_btw_quote(char *s1, char *s2);
int					check_var_exist(char **env, char *variable);
int					count_var_len(char *str);
int					count_between_quotes(char *str, char c);
int					count_string(char **env);
char				**create_env(char **env, int tofree);
int					count_quotes(char *str);
int					quotes(char *str);
int					syntax(char *s);
char				*negatif(char *str);
char				*positif(char *str);
char				*get_name_var(char *str);
char				*delete_quotes(char *str);
void				dupclose(int fd[2]);

#endif