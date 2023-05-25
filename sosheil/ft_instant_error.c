/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instant_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:26:06 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/25 10:17:34 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inside_quotes(char *line, int *i)
{
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] != '\"' && line[*i])
			(*i)++;
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] != '\'' && line[*i])
			(*i)++;
	}
}

int	enter_check(char *line)
{
	if (ft_strlen(line) == 0)
		return (1);
	return (0);
}

int	quote_check(char *line)
{
	int	i;
	int	single;
	int	dobble;

	i = 0;
	single = 0;
	dobble = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			single++;
		if (line[i] == '\"')
			dobble++;
		i++;
	}
	if (single % 2 != 0 || dobble % 2 != 0)
		return (1);
	return (0);
}

int	dobble_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	redir_check(char *line)
{
	if (l_redir_check(line) != 0)
		return (1);
	if (r_redir_check(line) != 0)
		return (1);
	if (opp_redir_check(line) != 0)
		return (1);
	if (opp_redir_check2(line) != 0)
		return (1);
	return (0);
}
