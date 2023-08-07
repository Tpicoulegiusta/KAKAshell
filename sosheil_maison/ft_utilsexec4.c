/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilsexec4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:25:15 by sboetti           #+#    #+#             */
/*   Updated: 2023/08/07 12:56:29 by sboetti          ###   ########.fr       */
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

int	is_builtin_exec(t_node *node)
{
	/*while (node)
	{
		if (node->type == cmd || node->type == builtin || node->type == opt)
			break ;
		node = node->next;
	}*/ //////delete if useless
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

t_node	*scan_hd(t_data *d, t_node *node)
{
	char	*limiter;
	int		i;

	i = 0;
	limiter = NULL;
	while (node)
	{
		if (node->type == piperino)
			i++;
		if (node->type == eof)
		{
			delnode(&d->lst, node);
			node = node->next;
			limiter = ft_strdup(node->str);
			enter_the_heredoc(d, limiter, i);
			delnode(&d->lst, node);
		}
		if (node)
			node = node->next;
	}
	node = d->lst.first;
	return (free(limiter), node);
}