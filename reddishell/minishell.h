/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:39:38 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/18 18:36:42 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# define NAME "turboshell% "

//RR = right redir, LR = left redir
enum	e_tok{str, piperino, rr, lr};

typedef struct s_node
{
	enum e_tok		type;
	char			*str;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_list
{
	int				len;
	t_node			*first;
	t_node			*last;
}				t_list;

typedef struct s_data
{
	char	**lextab;
}				t_data;

char	*getpath(char **envp, char *cmd);
char	**ft_quote_split(char *str, char sep);
char	*joinfree(char *s1, char *s2);
char	*joinfree2(char *s1, char c);
int		len(char *str);
int		ft_printf(const char *str, ...);
void	freetab(char **tab, int i);
void	free_execve(t_data *data);
char	*substr2(char *s, int start, int end);
char	**ft_split(char *s, char c);

//////// LIST ///////////////////////////

void	list_init(t_list *list);
void	addnode(t_list *list, char *str);
t_list	*create_list(char **tab, t_list *list);
void	freelist(t_list *lst);

//////// LEXER //////////////////////////

void	lexer(t_list *lst, char *line);
void	tokenizer(t_list *lst);

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
