/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:45:45 by sboetti           #+#    #+#             */
/*   Updated: 2023/06/01 12:10:10 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_init(t_list *list)
{
	list->len = 0;
	list->first = NULL;
	list->last = NULL;
}

void	addnode(t_list *list, char *str)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->str = NULL;
	new->path = NULL;
	new->str = joinfree(new->str, str);
	new->type = 0;
	new->quote = 0;
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
/*
void	delnode(t_list *list, t_node *node)
{
	if (!node->next && !node->prev)
	{
		list->first = NULL;
		list->last = NULL;
		free(node);
	}
	else if (!node->next)
	{
		list->last = list->last->prev;
		list->last->next = NULL;
		free(node);
	}
	else if (!node->prev)
	{
		list->first = list->first->next;
		list->first->prev = NULL;
		free(node);
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node);
	}
}*/



/*
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
}*/
