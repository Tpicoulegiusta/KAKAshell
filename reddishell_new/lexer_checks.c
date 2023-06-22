/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:15:28 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/22 14:22:06 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_copy(t_list *lst, char **copy)
{
	if (*copy != NULL)
	{
		addnode(lst, *copy);
		free(*copy);
		*copy = NULL;
	}
}
int	check_32(t_list *lst, char c, char **copy)
{
	if (c == 32)
	{
		if (*copy != NULL)
		{
			addnode(lst, *copy);
			lst->last->space = 1;
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
		check_copy(lst, copy);	
		tmp = joinfree2(tmp, c);
		addnode(lst, tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

int	quoted(t_list *lst, char *line, char **copy, int *i)
{
	int	start;

	if (line[*i] == '\"')
	{
		check_copy(lst, copy);
		start = (*i);
		(*i)++;
		while (line[*i] != '\"')
			(*i)++;
		*copy = substr2(line, start, *i + 1);
		check_copy(lst, copy);
		return (1);
	}
	if (line[*i] == '\'')
	{
		check_copy(lst, copy);
		start = (*i);
		(*i)++;
		while (line[*i] != '\'')
			(*i)++;
		*copy = substr2(line, start, *i + 1);
		check_copy(lst, copy);
		return (1);
	}
	return (0);
}
