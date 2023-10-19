/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:52:55 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/11 21:01:19 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_libstst;

void				*ft_freetab(char **tab);
char				*ft_realloc(char *s1, char *s2);

int					ft_atoi(const char *str);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isalpha(int c);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_lstsize(t_libstst *lst);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
char				**ft_split(char const *s, char *str);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strchr(char const *str, int c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strdup(char *src);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
char				*ft_strrchr(const char *s, int c);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_putstr_fd(char *s, int fd);
void				ft_bzero(void *s, size_t n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_lstadd_front(t_libstst **lst, t_libstst *new);
void				ft_lstadd_back(t_libstst **lst, t_libstst *new);
void				ft_lstclear(t_libstst **lst, void (*del)(void *));
void				ft_lstdelone(t_libstst *lst, void (*del)(void *));
void				ft_lstiter(t_libstst *lst, void (*f)(void *));
int					ft_strcmp(const char *s1, const char *s2);

t_libstst			*ft_lstnew(void *content);
t_libstst			*ft_lstlast(t_libstst *lst);
t_libstst			*ft_lstmap(t_libstst *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
