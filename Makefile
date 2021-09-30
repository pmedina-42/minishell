# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/22 21:22:10 by pmedina-          #+#    #+#              #
#    Updated: 2021/09/27 16:39:42 by lgomez-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

DIRLIBFT = libft

LIBFT = ${DIRLIBFT}/libft.a

RM = rm -rf

FILES = main \
	errors \
	env_utils \
	signals \
	load_cmds \
	add_path \
	load_files \
	files_utils \
	exec_line \
	run_commands \
	run_utils \
	wait_process \
	utils \
	replace_words \
	builtins/builtins \
	header \
	utils_str \
	builtins/cd_builtin \
	builtins/export_builtin \
	builtins/simple_builtins \
	builtins/echo_builtin \
	builtins/exit_builtin \
	builtins/export_utils


CFLAGS = -Wall -Wextra -Werror

SRCS = ${addsuffix .c, ${addprefix srcs/, ${FILES}}}

OBJS = ${SRCS:.c=.o}

MFLAGS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -pthread

${NAME}:	${LIBFT} ${OBJS}
	gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${MFLAGS}

all: ${NAME}

${LIBFT}:
	${MAKE} bonus -C ${DIRLIBFT}

clean:
	${RM} ${OBJS}
	${MAKE} fclean -C ${DIRLIBFT}

fclean:	clean
	${RM} ${NAME}

re:		fclean all
