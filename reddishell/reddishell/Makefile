# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 09:39:45 by rbulanad          #+#    #+#              #
#    Updated: 2023/05/11 19:26:20 by rbulanad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SOURCES		= minishell.c \
			  ft_split.c \
			  ft_strjoin.c \
			  getpath.c \
			  pipex.c \
			  printf/ft_hexa_func.c \
			  printf/ft_printf.c \
			  printf/ft_printf_func.c \
			  lists.c \
			  lexer.c
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
