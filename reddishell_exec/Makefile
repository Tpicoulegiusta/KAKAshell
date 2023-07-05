# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 09:39:45 by rbulanad          #+#    #+#              #
#    Updated: 2023/07/05 16:29:37 by rbulanad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SOURCES		= minishell.c \
			  ft_strjoin.c \
			  pipex.c \
			  lists.c \
			  lexer.c \
			  instant_err.c \
			  instant_err2.c \
			  freee.c \
			  ft_split.c \
			  redir_checks.c \
			  lexer_checks.c \
			  parser.c \
			  env_to_lst.c \
			  dlc_export.c \
			  dlc_env.c	\
			  executor.c \
			  var_env.c
OBJECTS		= ${SOURCES:.c=.o}
RM		= rm -f
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJECTS} 
	${CC} ${CFLAGS} ${OBJECTS} -o ${NAME} -lreadline

all: ${NAME}

clean:
	${RM} ${OBJECTS}
fclean: clean
	${RM} ${NAME}
re: fclean all

.PHONY: all clean fclean re
