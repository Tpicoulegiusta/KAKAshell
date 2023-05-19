SRCS = $(wildcard srcs/*.c) \
ft_printf/ft_arguments.c ft_printf/ft_printf.c ft_printf/ft_printf_utils.c \

SRCSTMP = ft_bzero.c ft_isalnum.c ft_memset.c \
ft_memcpy.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_strlen.c ft_memmove.c ft_strlcpy.c \
ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_sort_int_tab.c ft_strcmp.c \

OBJS = ${SRCS:.c=.o}

GCC = gcc -Wall -Wextra -Werror

NAME = libft.a

.c.o :
		@${GCC} -I ./libft.h -c $< -o ${<:.c=.o}

$(NAME) : ${OBJS}
		@ar rcs ${NAME} ${OBJS}

all : $(NAME)

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY : .c.o all bonus clean fclean re
