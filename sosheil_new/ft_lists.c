/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:45:45 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 18:10:50 by sboetti          ###   ########.fr       */
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
	new->str = joinfree(new->str, str);
	new->type = 0;
	new->space = 0;
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

void	delnode(t_list *list, t_node *node)
{
	if (!node->next && !node->prev)
	{
		list->first = NULL;
		list->last = NULL;
		ft_free_node(node);
	}
	else if (!node->next)
	{
		list->last = list->last->prev;
		list->last->next = NULL;
		ft_free_node(node);
	}
	else if (!node->prev)
	{
		list->first = list->first->next;
		list->first->prev = NULL;
		ft_free_node(node);
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		ft_free_node(node);
	}
}
