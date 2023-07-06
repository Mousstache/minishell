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

typedef struct s_data
{
	char	**path;
	char	**env;
	char	**cmd;
	int		nbcmd;
	int		outfile;
	int		infile;
	int		prev_pipe;
	int		here_doc;
	int		*pid;
	char	**tab;
	int		fd[2];
	t_here	*here;
	int		nbhere;
	bool	stop;
}	t_data;

typedef struct s_cmd
{
	char	**arg;
	char	*cmd;
	int		*redir;
	char	**tab;
	char	**files;
}	t_cmd;

void	free_all(char **tab);
char	*ft_gnl(int fd, int boolean);
void	error_free_exit(t_data *data);
void	ft_printtab(char **tab);
char	**path_finder(char **env);
void	dup_close(int fd, int fd2);
bool	here_doc(t_data *data, char *str);
int		isaredirection(char *str);
void	free_heredoc(t_data *data);
void	message(t_data *data);
void	waiting(t_data *data);
void	ft_close(t_data *data);
void	last_cmd(t_data *data, char **av);
t_data	*starton(void);
void	ctrlc(int sig);
int		quotes(char *str);
int		syntax(char *str);
char	*addspace(char *str);




#endif