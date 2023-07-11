DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = minishell
LIB_F = libft
LIB = libft.a
GCCFLG = gcc -Wall -Wextra -Werror -I minishell.h

SRCS = minishell.c ft_ministrjoin.c ft_lists.c \
		ft_lexer.c ft_freee.c \
		ft_instant_error.c ft_utils.c \
		ft_redir_checks.c ft_instant_error2.c \
		ft_check_lexer.c ft_parser.c ft_pwd.c \
		ft_cd.c ft_env_to_list.c ft_built_exit.c \
		ft_echo.c ft_check_parser.c ft_executor.c \
		ft_var_env.c ft_built_export.c ft_parser2.c \
		ft_built_env.c ft_utilsexec1.c ft_utilsexec2.c \
		ft_utilsexec3.c ft_utilsexec4.c ft_signals.c \
		ft_exportutils1.c ft_exportutils2.c ft_exportutils3.c \

OBJ = ./objs

OBJS = $(addprefix $(OBJ)/, ${SRCS:.c=.o})

all: credit $(NAME)

$(NAME): ${OBJS} $(LIB_F)/$(LIB)
	@echo "$(GREEN)Minishell is up to date!${DEFAULT}"
	@$(GCCFLG) $(LIB_F)/$(LIB) -o $(NAME) $(OBJS) -lreadline -L /Users/sboetti/.brew/opt/readline/lib -I /Users/sboetti/.brew/opt/readline/include 


$(LIB_F)/$(LIB):
	@make -C $(LIB_F)

$(OBJ)/%.o: ./%.c
	@mkdir -p ${OBJ}
	@$(GCCFLG) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@make clean -C $(LIB_F)
	@echo "${RED}Making Clean 🗑️${DEFAULT}"

fclean:
	@rm -rf $(OBJ)
	@rm -rf $(NAME)
	@make fclean -C $(LIB_F)
	@echo "${RED}Making Fclean 🗑️${DEFAULT}"

re: fclean all

credit:
	@echo "$(MAGENTA)███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(DEFAULT)"
	@echo "               Made by : fleriche and sboetti"