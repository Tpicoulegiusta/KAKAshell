/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:38:52 by sboetti           #+#    #+#             */
/*   Updated: 2023/06/01 11:53:25 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# define NAME "\e[0;94mPROMPETEUH% \e[0;97m"

//RR = right redir, LR = left redir
enum	e_tok{str, piperino, rr, lr, cmd, venv};

typedef struct s_node
{
	enum e_tok		type;
	char			*str;
	char			*path;
	int				quote;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_list
{
	int				len;
	t_node			*first;
	t_node			*last;
	struct s_node	node;
}				t_list;

typedef struct s_data
{
	char	**lextab;
}				t_data;

char	*getpath(char **envp, char *cmd);
char	**ft_minisplit(char *s, char c);
char	*joinfree(char *s1, char *s2);
char	*joinfree2(char *s1, char c);
void	freetab(char **tab, int i);
void	free_execve(t_data *data);
char	*substr2(char *s, int start, int end);

//////// LIST ///////////////////////////

void	list_init(t_list *list);
void	addnode(t_list *lst, char *str);
t_list	*create_list(char **tab, t_list *list);
void	freelst(t_list *lst);

//////// LEXER //////////////////////////

int		check_32(t_list *lst, char c, char **copy);
int		check_spe(t_list *lst, char c, char **copy);
int		quoted(t_list *lst, char *line, char **copy, int *i);
void	lexer(t_list *lst, char *line);
void	tokenizer(t_list *lst);

//////// PARSER ////////////////////////

void	parser(t_list *lst, char **envp);
char	*ft_pathjoin(char *s1, char *s2);
char	*find_envline(char **envp, char *search);

//////// EXEC //////////////////////////

void	exec(t_data *data, char **envp);

//////// CHECKER ////////////////////////

void	inside_quotes(char *line, int *i);
int		quote_check(char *line);
int		dobble_pipe(char *line);
int		enter_check(char *line);
int		l_redir_check(char *line);
int		r_redir_check(char *line);
int		opp_redir_check(char *line);
int		opp_redir_check2(char *line);
int		redir_check(char *line);
int		semi(char *line);
int		backslash(char *line);

#endif
