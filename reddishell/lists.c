/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:03 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/12 12:39:27 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*list_init(t_list *list)
{
	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->len = 0;
	list->first = NULL;
	list->last = NULL;
	return (list);
}

void	addnode(t_list *list, char *tok)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	new->tok = NULL;
	new->tok = joinfree(new->tok, tok);
	new->type = 0;
	if (list->last == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		list->first = new;
		list->last = new;
	}
	else
	{
		list->last->next = new;
		new->prev = list->last;
		list->last = new;
		new->next = NULL;
	}
	list->len++;
}

t_list	*create_list(char **tab, t_list *list)
{
	int	i;

	list = list_init(list);
	i = 0;
	while (tab[i])
	{
		addnode(list, tab[i++]);
	}
	return (list);
}
