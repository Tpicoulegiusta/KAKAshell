/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:38:52 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/19 11:52:44 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# define NAME "PROMPETEUH% "

//RR = right redir, LR = left redir
enum	e_tok{str, piperino, rr, lr};

typedef struct s_node
{
	enum e_tok		type;
	char			*str;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_lst
{
	int				len;
	t_node			*first;
	t_node			*last;
}				t_lst;

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
void	list_init(t_lst *list);
void	addnode(t_lst *lst, char *str);
t_lst	*create_list(char **tab, t_lst *list);
void	freelst(t_lst *lst);

//////// LEXER //////////////////////////
void	lexer(t_lst *lst, char *line);
void	tokenizer(t_lst *lst);

//////// PARSER ////////////////////////

//////// EXEC //////////////////////////
void	exec(t_data *data, char **envp);

//////// CHECKER ////////////////////////
int		quote_check(char *line);
int		dobble_pipe(char *line);
int		enter_check(char *line);
int		l_redir_check(char *line);
int		r_redir_check(char *line);
int		opp_redir_check(char *line);
int		opp_redir_check2(char *line);
int		redir_check(char *line);

#endif
