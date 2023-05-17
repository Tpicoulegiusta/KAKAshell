/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:13:57 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/17 17:19:53 by rbulanad         ###   ########.fr       */
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
		addnode(lst, joinfree2(tmp, c));
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
		{
			*copy = joinfree2(*copy, line[*i]);
			(*i)++;
		}
		return (1);
	}
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] != '\'')
		{
			*copy = joinfree2(*copy, line[*i]);
			(*i)++;
		}
		return (1);
	}

	return (0);
}

void	lexer(t_list *lst, char *line)
{
	char	*copy;
	int		quote;
	int		i;

	i = 0;
	quote = 0;
	copy = NULL;
	while (line[i])
	{
		if (quoted(line, &copy, &i) == 1)
			i++;
		else if (check_32(lst, line[i], &copy) == 1)
			i++;
		else if (check_spe(lst, line[i], &copy) == 1)
			i++;
		else
			copy = joinfree2(copy, line[i++]);
	}
	if (copy)
	{
		addnode(lst, copy);
		free(copy);
		copy = NULL;
	}
}
/*
void	tokenizer(t_data *data, t_list *lst)
{
	t_tok	*tmp;

	if (lst->first)
		freelst(lst);
	lst = create_list(data->lextab, lst);
	tmp = lst->first;
	while (tmp)
	{
		printf("tok = %s\n", tmp->tok);
		tmp = tmp->next;
	}
}*/
