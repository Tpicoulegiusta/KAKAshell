# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 09:39:45 by rbulanad          #+#    #+#              #
#    Updated: 2023/05/16 15:19:45 by rbulanad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SOURCES		= minishell.c \
			  ft_strjoin.c \
			  getpath.c \
			  pipex.c \
			  printf/ft_hexa_func.c \
			  printf/ft_printf.c \
			  printf/ft_printf_func.c \
			  lists.c \
			  lexer.c \
			  instant_err.c \
			  freee.c \
			  ft_split.c
OBJECTS		= ${SOURCES:.c=.o}
RM		= rm -f
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJECTS} 
	${CC} -lreadline ${CFLAGS} ${OBJECTS} -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJECTS}
fclean: clean
	${RM} ${NAME}
re: fclean all

.PHONY: all clean fclean re
