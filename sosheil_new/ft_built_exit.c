/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:03:51 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/05 11:09:30 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_built_exit(t_node *tmp)
{
	int	i;

	i = -1;
	if (!tmp->next)
	{
		exit(127);
	}
	tmp = tmp->next;
	while (tmp->str[++i])
	{
		if (tmp->str[i] == '|')
			break ;
		if (!ft_isdigit(tmp->str[i]))
		{
			printf("numeric argument required\n");
			exit (255);
		}
	}
	if ((tmp->type == piperino) || (tmp->next && tmp->next->type == piperino))
		return (1);
	exit(ft_atoi(tmp->str) % 256);
}
