/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:38:52 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/15 12:46:13 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# define NAME "PROMPETEUH% "

typedef struct s_tok
{
	int				type;
	char			*tok;
	struct s_tok	*next;
	struct s_tok	*prev;
}				t_tok;

typedef struct s_lst
{
	int				len;
	t_tok			*first;
	t_tok			*last;
}				t_lst;

typedef struct s_data
{
	char	**lextab;
}				t_data;

char	*getpath(char **envp, char *cmd);
char	**ft_minisplit(char *s, char c);
char	**ft_split(const char *s, char c); ////////////////////////////
char	*joinfree(char *s1, char *s2);
char	*joinfree2(char *s1, char c);
void	freetab(char **tab, int i);
void	free_execve(t_data *data);
char	*substr2(char *s, int start, int end);

//////// LIST ///////////////////////////
t_lst	*create_list(char **tab, t_lst *list);
void	freelst(t_lst *lst);

//////// LEXER //////////////////////////
char	**lexer(char *prompt);
void	tokenizer(t_data *data, t_lst *lst);

//////// PARSER ////////////////////////

//////// EXEC //////////////////////////
void	exec(t_data *data, char **envp);

//////// CHECKER ////////////////////////
int		quote_check(char *line);
int		dobble_pipe(char *line);
int		enter_check(char *line);

#endif
