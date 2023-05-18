/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instant_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:56:35 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/18 18:34:23 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	enter_check(char *line)
{
	if (len(line) == 0)
		return (free(line), 1);
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
