/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:50:04 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/13 17:53:28 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_pipe(int type)
{
	if (type >= 1 && type <= 5)
		return (1);
	return (0);
}

int	check_fds(t_data *d)
{
	if (d->fd_in < 0)
	{
		(printf("INFILE ERROR\n"));
		return (1);
	}
	if (d->fd_out < 0)
	{
		(printf("OUTFILE ERROR\n"));
		return (1);
	}
	return (0);
}

int	pipe_count(t_data *d)
{
	t_node	*node;
	int		count;

	count = 0;
	node = d->lst.first;
	while (node)
	{
		if (node->type == piperino)
			count++;
		node = node->next;
	}
	d->fd_hd = malloc(sizeof(int *) * count);
	return (count);
}
