# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 00:33:37 by maheraul          #+#    #+#              #
#    Updated: 2022/11/25 02:55:51 by maheraul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = 		ft_src.c\
			ft_printf.c \

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}:	${OBJS}
		ar rcs ${NAME} ${OBJS}

norme:
	norminette ${SRCS}

clean:
	rm -rf ${OBJS}

fclean:	clean
	rm -rf ${NAME}

re : fclean ${NAME}

.PHONY : all norme clean fclean re
