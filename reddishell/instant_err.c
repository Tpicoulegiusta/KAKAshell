/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instant_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:56:35 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/24 15:10:22 by rbulanad         ###   ########.fr       */
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
	if (len(line) == 0)
		return (free(line), 1);
	return (0);
}

int	quote_check(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			inside_quotes(line, &i);
			if (line[i] == '\0')
				return (1);
		}
		else if (line[i] == '\"')
		{
			inside_quotes(line, &i);
			if (line[i] == '\0')
				return (1);
		}
	}
	return (0);
}

int	dobble_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		inside_quotes(line, &i);
		if (line[i] == '|')
		{
			i++;
			while (line[i] == 32)
				i++;
			if (line[i] == '|')
				return (1);
		}
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
