/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:03 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/17 13:27:11 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_init(t_list *list)
{
	/*list = malloc(sizeof(t_list));
	if (!list)
		return ;*/ //ca PUE samer
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
	new->tok = 0;
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

void	freelist(t_list *lst)
{
	t_node	*tmp;
	t_node	*next;

	tmp = lst->first;
	while (tmp)
	{
		next = tmp->next;
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
