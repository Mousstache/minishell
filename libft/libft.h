/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:47:03 by motroian          #+#    #+#             */
/*   Updated: 2023/08/02 22:30:34 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_liste
{
	void			*content;
	struct s_liste	*next;
}					t_liste;

// is
int					ft_isalpha(int nb);
int					ft_isdigit(int nb);
int					ft_isalnum(int nb);
int					ft_isascii(int nb);
int					ft_isprint(int nb);
int					ft_isspace(int nb);

// mem
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

// str
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_strcmp(char *s1, char *s2);
void				ft_putstr_e(char *str);

// rest
int					ft_toupper(int c);
int					ft_tolower(int c);
// int				ft_atoi(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_realloc(char *s1, char *s2);

// FD
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

// //list
// t_list			*ft_lstnew(void *content);
// t_liste			*ft_lstlast(t_liste *lst);
t_liste				*ft_lstmap(t_liste *lst, void *(*f)(void *),
						void (*del)(void *));

// int				ft_lstsize(t_liste *lst);

// void			ft_lstadd_front(t_liste **lst, t_liste *new);
// void			ft_lstadd_back(t_liste **lst, t_liste *new);
void				ft_lstdelone(t_liste *lst, void (*del)(void *));
void				ft_lstclear(t_liste **lst, void (*del)(void *));
void				ft_lstiter(t_liste *lst, void (*f)(void *));

// ft_printf
int					ft_printf(const char *s, ...);
int					ft_putnbr(int nb);
int					ft_putchar(int c);
int					ft_putstr(char *str);
int					ft_count(int nb);
int					h(unsigned long int nb, char *base);
// size_t	ft_strlen(char *str);

#endif
