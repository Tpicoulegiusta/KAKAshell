/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:38:52 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/07 18:13:43 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <readline/readline.h>
# include <readline/history.h>
# define NAME "\e[0;94mPROMPETEUH% \e[0;97m"

//rr = right redir, lr = left redir
enum	e_tok{str, piperino, out, in, eof, append, cmd, venv, builtin};
//			   0      1       2   3   4      5      6     7      8

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
	t_list	lst;
	t_list	envlst;
	t_list	sort_env;
	int		*pid;
	int		i;
	int		fd[2];
	int		prev_fd;
	int		fd_in;
	int		fd_out;
	int		sfd_in;
	int		sfd_out;
}				t_data;

///////// UTILS /////////////////////////

char	*getpath(char *cmd, t_list *envlst);
char	*absolutepath(char *cmd);
int		syntax_checker(t_list *lst);
void	dollaz(t_list *lst, t_list *envlst);
int		ft_find(char *str, char *search);
int		is_space(char *str);
int		spe_char(char c);
void	unquoter(t_list *lst);
char	*ft_ministrjoin(char *s1, char *s2);
char	*joinfree(char *s1, char *s2);
char	*joinfree2(char *s1, char c);
void	freetab(char **tab);
void	free_execve(t_data *data);
char	*substr2(char *s, int start, int end);
char	*ft_ministrrchr(char *s, char c);
char	*ft_ministrchr(char *s, char c);
t_node	*find_node(char *key, t_list *env);
int		is_builtin(char *str);

//////// LIST ///////////////////////////

void	ft_env_to_list(t_list *envlst, char **envp);
void	list_init(t_list *list);
void	addnode(t_list *lst, char *str);
void	delnode(t_list *list, t_node *node);
t_list	*create_list(char **tab, t_list *list);
void	freelist(t_list *lst);
void	ft_free_all(t_list *lst1, t_list *lst2);
void	print_lst(t_list *lst);

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

//////// EXEC //////////////////////////

void	executor(t_data *d);

/////// BUILTINS ///////////////////////

int		builtins(t_data *d);
int		export_unset(t_node *node, t_list *envlst, t_list *sort_envlst);
void	check_env(t_list *envlst, t_node *node);
int		other_check(t_node *tmp, t_list *envlst);
int		another_check(t_list *envlst, t_node *tmp);
int		and_another_check(t_node *tmp);
int		ft_built_exit(t_node *tmp);

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
