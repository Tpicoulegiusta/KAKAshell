/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:07:44 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 12:46:43 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *envlst)
{
	t_node	*tmp;

	tmp = NULL;
	if (envlst->first)
	{
		tmp = envlst->first;
		while (tmp)
		{
			printf("%s\n", tmp->str);
			tmp = tmp->next;
		}
		if (tmp == NULL && tmp->prev == NULL)
			return ;
	}
	return ;
}

void	check_env(t_list *envlst, t_node *node)
{
	if (ft_strcmp(node->str, "env") == 0)
	{
		if (node->next && node->next->type != piperino)
			printf("ENV ERROR\n");
		else
			print_env(envlst);
	}
}
