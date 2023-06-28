/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlc_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:23:28 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/19 14:10:41 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *envlst)
{
	t_node	*tmp;

	tmp = envlst->first;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

void	check_env(t_list *envlst, t_node *node)
{
	if (ft_strcmp(node->str, "env") == 0)
	{
		if (node->next)
			printf("ENV ERROR\n");
		else
			print_env(envlst);
	}
}
