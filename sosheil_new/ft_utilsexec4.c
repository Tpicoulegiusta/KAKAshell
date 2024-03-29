/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilsexec4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:25:15 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/14 19:52:20 by sboetti          ###   ########.fr       */
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

int	is_builtin_exec(t_node *node)
{
	while (node)
	{
		if (node->type == cmd || node->type == builtin || node->type == opt)
			break ;
		node = node->next;
	}
	if (ft_strcmp(node->str, "echo") == 0)
		return (1);
	if (ft_strcmp(node->str, "cd") == 0)
		return (1);
	if (ft_strcmp(node->str, "pwd") == 0)
		return (1);
	if (ft_strcmp(node->str, "export") == 0)
		return (1);
	if (ft_strcmp(node->str, "unset") == 0)
		return (1);
	if (ft_strcmp(node->str, "env") == 0)
		return (1);
	if (ft_strcmp(node->str, "exit") == 0)
		return (1);
	return (0);
}
