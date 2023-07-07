/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:18:37 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/07 17:42:38 by sboetti          ###   ########.fr       */
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
		if (lst->last)
			lst->last->space = 1;
		return (1);
	}
	return (0);
}

int	check_spe(t_list *lst, char *line, int i, char **copy)
{
	char	*tmp;

	tmp = NULL;
	if (line[i] == '|' || line[i] == '>' || line[i] == '<')
	{
		check_copy(lst, copy);
		tmp = joinfree2(tmp, line[i]);
		addnode(lst, tmp);
		if (line[i + 1] == 32)
			lst->last->space = 1;
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
		start = (*i) + 1;
		(*i)++;
		while (line[*i] != '\"')
			(*i)++;
		*copy = substr2(line, start, *i);
		check_copy(lst, copy);
		return (1);
	}
	if (line[*i] == '\'')
	{
		check_copy(lst, copy);
		start = (*i) + 1;
		(*i)++;
		while (line[*i] != '\'')
			(*i)++;
		*copy = substr2(line, start, *i);
		check_copy(lst, copy);
		return (1);
	}
	return (0);
}
