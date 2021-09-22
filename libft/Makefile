# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 12:43:32 by lgomez-d          #+#    #+#              #
#    Updated: 2021/09/02 18:56:42 by lgomez-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
RM		= rm -f
SRCS	= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c \
ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstmap.c ft_strncpy.c get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \
ft_str_is_nbr.c ft_array_len.c ft_str_in_set.c ft_delete_set.c ft_split_set.c \
ft_strndup.c ft_isspace.c ft_substrdel.c ft_strposchr.c ft_strcmp.c

CFLAGS	= -Wall -Wextra -Werror

OBJ		= ${SRCS:.c=.o}

SBONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBONUS	= ${SBONUS:.c=.o}

${NAME}:	${OBJ}
		ar rc ${NAME} ${OBJ}

all:	${NAME}

bonus:	${OBJ} ${OBONUS}
		ar -rv ${NAME} ${OBJ} ${OBONUS}

clean:
		${RM} ${OBJ} ${OBONUS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all bonus clean fclean re