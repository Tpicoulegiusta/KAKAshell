/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:39:38 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/11 19:25:00 by rbulanad         ###   ########.fr       */
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

//enum token_type{string, pipe};

typedef struct s_data
{
	char	**lextab;
	//char	**argexec;
	//char 	*path;
}				t_data;

typedef struct s_tok
{
	int				type;
	char			*tok;
	struct s_tok	*next;
	struct s_tok	*prev;
}				t_tok;

typedef struct s_list
{
	int				len;
	t_tok			*first;
	t_tok			*last;
}				t_list;

char	*getpath(char **envp, char *cmd);
char	**ft_split(char *s, char c);
char	*joinfree(char *s1, char *s2, char c);
int		len(char *str);
int		ft_printf(const char *str, ...);
void	freetab(char **tab, int i);
void	free_execve(t_data *data);
//////// LIST ///////////////////////////
t_list	*create_list(char **tab, t_list *list);
//////// LEXER //////////////////////////
void	lexer(char *prompt);
void	tokenizer(t_data *data);
//////// PARSER ////////////////////////
//////// EXEC //////////////////////////
void	exec(t_data *data, char **envp);
//////// CHECKER ////////////////////////
int		quote_check(char *line);
int		dobble_pipe(char *line);

#endif
