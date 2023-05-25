/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:34:19 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/25 10:24:46 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	l_redir_check(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		inside_quotes(line, &i);
		if (line[i] == '>' && line [i + 1] == '<')
			return (1);
		i++;
	}
	i = 0;
	while (line[i] && line[i + 1])
	{
		inside_quotes(line, &i);
		if (line[i] == '<' && line[i + 1] == 32)
		{
			i++;
			while (line[i] == 32)
				i++;
			if (line[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

int	r_redir_check(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		inside_quotes(line, &i);
		if (line[i] == '>' && line[i + 1] == 32)
		{
			i++;
			while (line[i] == 32)
				i++;
			if (line[i] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

int	opp_redir_check(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		inside_quotes(line, &i);
		if (line[i] == '<' && line[i + 1] == 32)
		{
			i++;
			while (line[i] == 32)
				i++;
			if (line[i] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

int	opp_redir_check2(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		inside_quotes(line, &i);
		if (line[i] == '>' && line[i + 1] == 32)
		{
			i++;
			while (line[i] == 32)
				i++;
			if (line[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}
