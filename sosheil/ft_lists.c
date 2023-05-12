/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:45:45 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/12 14:32:59 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*list_init(t_lst *list)
{
	list = malloc(sizeof(t_lst));
	if (!list)
		return (NULL);
	list->len = 0;
	list->first = NULL;
	list->last = NULL;
	return (list);
}

void	addnode(t_lst *list, char *tok)
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

t_lst	*create_list(char **tab, t_lst *list)
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
