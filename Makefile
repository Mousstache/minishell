SRCS = $(addprefix exec/, main.c minishell_utils.c here_docs.c minishell.c minishell_utils_2.c addspace.c) \
		$(addprefix parsing/, valid.c) \
		#$(addprefix builtin/, echo.c) \

NAME = minishell

INC = -Iinclude

FLAGS = -g3 -Wall -Werror -Wextra

OBJS = ${SRCS:.c=.o}

LIBFT = libft.a

${NAME} : ${OBJS} ${LIBFT}
			make -C libft/ all
			mv libft/libft.a ./
			cc ${FLAGS} ${INC} $(OBJS) -o $(NAME) libft.a -lreadline

${LIBFT}:
	make -C libft/ all
	mv libft/libft.a ./

all : ${NAME}

%.o:%.c
		cc ${FLAGS} ${INC}  -c $< -o $@

leaks: $(NAME)
	valgrind --suppressions=suppressions.txt --leak-check=full --show-leak-kinds=all --track-fds=yes   ./minishell

clean :
		make -C ./libft/ clean
		rm -rf ${OBJS}

fclean : clean
		rm -rf ${NAME} ${LIBFT}
		make -C ./libft/ fclean

re : fclean all

.PHONY : all  clean fclean re libft NAME 



