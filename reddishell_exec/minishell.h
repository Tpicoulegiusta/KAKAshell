/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:39:38 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/13 16:45:53 by rbulanad         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# define NAME "turboshell% "

//RR = right redir, LR = left redir
enum	e_tok{str, piperino, cmd, venv, builtin, opt, out, in, eof, append};
//			  0       1       2    3   		4     5    6   	7   8		9

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
	char	*argpath;
	char	**tabexec;
	char	**envtab;
	char	*stock_hd;
	t_list	lst;
	t_list	envlst;
	t_list	sort_env;
	int		numpipe_hd;
	int		is_in;
	int		is_out;
	int		scan_pipe;
	int		*pid;
	int		i_hd;
	int		i_pid;
	int		builtin;
	int		**fd_hd;
	int		fd[2];
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
int		is_builtin(char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
char	*ft_ministrjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	if_else_double(t_list *sort_envlst, t_list *envlst, char *str);
t_node	*find_node(char *key, t_list *env);
char	*ft_strdup(char *s1);
char	**lst_to_tab(t_node *node);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

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
int		is_cmd(char *str, t_list *envlst);
void	unquoter(t_list *lst);

//////// BUILTINS //////////////////////

int		export_unset(t_node *node, t_list *envlst, t_list *sort_envlst);
void	check_env(t_list *envlst, t_node *node);
int		ft_built_exit(t_node *tmp);
int		ft_cd(t_data *d, t_node *tmp);
int		ft_echo(t_node *tmp);
int		ft_pwd(t_node *tmp, t_list *env);

//////// EXEC //////////////////////////

void	executor(t_data *d);
int		exec_builtin_checks(int builtin, t_node *node);
int		exec_builtin_checks_pipe(int builtin, t_node *node);
void	child_func(t_data *d, t_node *node);
void	child_func_pipes(t_data *d, t_node *node);
int		check_fds(t_data *d);
t_node	*executor_body(t_data *d, t_node *node, int numpipe);
int		execute(t_data *d, t_node *node, int numpipe);
int		execute_pipes(t_data *d, t_node *node, int numpipe);
t_node	*scan_out_infiles(t_data *d, t_node *node);
char	*path_check(char *cmd, t_list *envlst);
void	init_fds(t_data *d);
int		pipe_count(t_data *d);
void	close_fds(t_data *d);

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
