/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:03 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/26 19:09:15 by rbulanad         ###   ########.fr       */
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

void	freelist(t_list *lst)
{
	t_node	*tmp;
	t_node	*next;

	tmp = lst->first;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = next;
	}
	lst->len = 0;
}

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
