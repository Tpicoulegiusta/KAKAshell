/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:04:39 by tpicoule          #+#    #+#             */
/*   Updated: 2023/05/10 16:18:17 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_lexer
{
	char *prompt;
}	t_lexer;

typedef struct s_parser
{
	char **lines;
}	t_parser;

typedef struct s_exec
{
	char	*cmd;
}	t_exec;

#endif