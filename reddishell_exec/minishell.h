/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:39:38 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/28 17:35:11 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define NAME "turboshell% "

//RR = right redir, LR = left redir
enum	e_tok{str, piperino, out, in, eof, append, cmd, venv, builtin};
//			  0       1       2    3   4     5      6     7      8

typedef struct s_node
{
	enum e_tok		type;
	char			*str;
	int				space;
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
	t_list	lst;
	t_list	envlst;
	t_list	sort_env;
	int		pid;
	int		fd[2];
	int		prev_fd;
	int		fd_in;
	int		fd_out;
	int		sfd_in;
	int		sfd_out;
}				t_data;

///////// UTILS /////////////////////////

char	**ft_quote_split(char *str, char sep);
char	*joinfree(char *s1, char *s2);
char	*joinfree2(char *s1, char c);
int		len(char *str);
void	freetab(char **tab);
void	free_execve(t_data *data);
char	*substr2(char *s, int start, int end);
char	**ft_split(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_find(char *str, char *search);
int		spe_char(char c);
char	*absolutepath(char *cmd);
char	*getpath(char *cmd, t_list *envlst);

//////// LIST ///////////////////////////

void	lst_init(t_list *list);
void	addnode(t_list *list, char *str);
t_list	*create_list(char **tab, t_list *list);
void	freelist(t_list *lst);
void	print_lst(t_list *lst);
void	delnode(t_list *list, t_node *node);
void	env_to_lst(t_list *envlst, char **envp);

//////// LEXER //////////////////////////

int		check_32(t_list *lst, char c, char **copy);
int		check_spe(t_list *lst, char *line, int i, char **copy);
int		quoted(t_list *lst, char *line, char **copy, int *i);
void	lexer(t_list *lst, char *line);
void	tokenizer(t_list *lst);

//////// PARSER ////////////////////////

int		parser(t_list *lst, t_list *envlst);
char	*ft_pathjoin(char *s1, char *s2);
char	*find_envline(char **envp, char *search);
void	dollaz(t_list *lst, t_list *envlst);

//////// BUILTINS //////////////////////

void	export_unset(t_node *node, t_list *envlst, t_list *sort_envlst);
void	check_env(t_list *envlst, t_node *node);

//////// EXEC //////////////////////////

void	executor(t_data *d, char **envp);

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
