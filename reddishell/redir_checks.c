/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:23:05 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/18 18:37:45 by rbulanad         ###   ########.fr       */
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
