/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:50:04 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/12 17:48:48 by rbulanad         ###   ########.fr       */
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
	{
		puts("FDIN");
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out < 0)
	{
		(printf("OUTFILE ERROR\n"));
		return (1);
	}
	if (fd_out)
	{
		puts("FDOUT");
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
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
