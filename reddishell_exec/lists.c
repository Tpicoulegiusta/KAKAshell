/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:03 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/13 17:23:12 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_init(t_list *list)
{
	list->len = 0;
	list->first = NULL;
	list->last = NULL;
}

int	is_space(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)
		{
			str = substr2(str, 0, i);
			return (1);
		}
		i++;
	}
	return (0);
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
		free(node->str);
		free(node);
	}
	else if (!node->next)
	{
		list->last = list->last->prev;
		list->last->next = NULL;
		free(node->str);
		free(node);
	}
	else if (!node->prev)
	{
		list->first = list->first->next;
		list->first->prev = NULL;
		free(node->str);
		free(node);
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node->str);
		free(node);
	}
}

void	freelist(t_list *lst)
{
	t_node	*tmp;
	t_node	*next;

	tmp = lst->first;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->str)
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
