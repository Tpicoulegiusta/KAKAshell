/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freee.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:22:29 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 18:36:52 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freetabpath(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i++]);
	}
	free(tab);
	tab = NULL;
	return ;
}

void	ft_free_node(t_node *node)
{
	if (node)
	{
		node->next = NULL;
		node->prev = NULL;
		free(node->str);
	}
	free(node);
	node = NULL;
	return ;
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
		ft_free_node(tmp);
		tmp = next;
	}
	lst->len = 0;
}

void	ft_free_all(t_list *lst1, t_list *lst2)
{
	if (lst1)
		freelist(lst1);
	if (lst2)
		freelist(lst2);
	return ;
}
