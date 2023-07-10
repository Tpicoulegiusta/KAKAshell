/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:50:04 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/09 16:53:23 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_pipe(int type)
{
	if (type >= 1 && type <= 5)
		return (1);
	return (0);
}

int	check_fds(int fd_in, int fd_out)
{
	if (fd_in < 0)
	{
		(printf("INFILE ERROR\n"));
		return (1);
	}
	if (fd_in)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out < 0)
	{
		(printf("OUTFILE ERROR\n"));
		return (1);
	}
	if (fd_out)
		dup2(fd_out, STDOUT_FILENO);
	return (0);
}

int	pipe_count(t_list *lst)
{
	t_node	*node;
	int		count;

	count = 0;
	node = lst->first;
	while (node)
	{
		if (node->type == piperino)
			count++;
		node = node->next;
	}
	return (count);
}
