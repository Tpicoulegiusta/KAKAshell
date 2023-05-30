/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:15:28 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/26 18:01:02 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_32(t_list *lst, char c, char **copy)
{
	if (c == 32)
	{
		if (*copy != NULL)
		{
			addnode(lst, *copy);
			free(*copy);
			*copy = NULL;
		}
		return (1);
	}
	return (0);
}

int	check_spe(t_list *lst, char c, char **copy)
{
	char	*tmp;

	tmp = NULL;
	if (c == '|' || c == '>' || c == '<')
	{
		if (*copy != NULL)
		{
			addnode(lst, *copy);
			free(*copy);
			*copy = NULL;
		}
		tmp = joinfree2(tmp, c);
		addnode(lst, tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

int	dollar_check(t_list *lst, char *line, char **copy, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (line[*i] == '$')
	{
		if (*copy != NULL)
		{
			addnode(lst, *copy);
			free(*copy);
			*copy = NULL;
		}
		while (line[*i] && line[*i] != 32)
				tmp = joinfree2(tmp, line[(*i)++]);
		addnode(lst, tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

int	quoted(char *line, char **copy, int *i)
{
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] != '\"')
			*copy = joinfree2(*copy, line[(*i)++]);
		return (1);
	}
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] != '\'')
			*copy = joinfree2(*copy, line[(*i)++]);
		return (1);
	}
	return (0);
}
