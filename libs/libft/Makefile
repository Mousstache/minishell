# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: motroian <motroian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 00:33:37 by maheraul          #+#    #+#              #
#    Updated: 2023/08/12 18:08:34 by motroian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3

SRCS = 		ft_isalpha.c\
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strcat.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c\
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_putendl_fd.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_realloc.c \
			ft_itoa.c \
			ft_split.c\
			ft_strtrim.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_strcmp.c

BONUS =		ft_lstnew.c\
			ft_lstsize.c\
			ft_lstadd_front.c\
			ft_lstadd_back.c\
			ft_lstlast.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c\


OBJS = ${SRCS:.c=.o}

BONUS_OBJS = ${BONUS:.c=.o}

all: ${NAME}

${NAME}:	${OBJS} ${BONUS_OBJS}
		ar rcs libft.a ${OBJS} ${BONUS_OBJS}

bonus: ${OBJS} ${BONUS_OBJS}
	ar rcs libft.a ${OBJS} ${BONUS_OBJS}

#so:
#	${CC} -nostartfiles -shared -o libft.so ${CFLAGS} ${SRCS} ${BONUS}

norme:
	norminette ${SRCS} ${BONUS}

clean:
	rm -rf ${OBJS}	${BONUS_OBJS}

fclean:	clean
	rm -rf ${NAME}

re : fclean ${NAME}

.PHONY : all bonus norme clean fclean re
.SILENT: