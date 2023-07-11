/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:03:51 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 17:01:19 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verif_if_pipe(t_node *tmp)
{
	if ((tmp->type == piperino) || (tmp->next && tmp->next->type == piperino))
		return ;
	exit(ft_atoi(tmp->str) % 256);
}

int	ft_built_exit(t_node *tmp)
{
	int	i;

	i = -1;
	if (ft_strcmp(tmp->str, "exit") == 0)
	{
		if (tmp->prev && tmp->prev->type == piperino)
			return (0);
		if (!tmp->next)
			exit(127);
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
		verif_if_pipe(tmp);
	}
	return (0);
}
