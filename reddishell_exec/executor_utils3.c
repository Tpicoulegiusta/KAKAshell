/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:47:25 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/12 17:51:47 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(t_data *d)
{
	d->fd_in = 0;
	d->fd_out = 0;
	d->sfd_in = dup(STDIN_FILENO);
	d->sfd_out = dup(STDOUT_FILENO);
}

t_node	*open_infile(t_data *d, t_node *node)
{
	t_node *tmp;
	
	tmp = node;
	if (node->type == in)
	{
		delnode(&d->lst, node);
		node = node->next;
		if (d->fd_in)
			close(d->fd_in);
		d->fd_in = open(node->str, O_RDONLY, 0777);
		delnode(&d->lst, node);
		tmp = node;
		//printf("fdIN = %d, fdOUT = %d\n", d->fd_in, d->fd_out);
	}
	return (tmp);
}

t_node	*open_outfile(t_data *d, t_node *node)
{
	t_node *tmp;

	tmp = node;
	if (node->type == out)
	{
		delnode(&d->lst, node);
		node = node->next;
		if (d->fd_out)
			close(d->fd_out);
		d->fd_out = open(node->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		delnode(&d->lst, node);
		tmp = node;
		//printf("fdIN = %d, fdOUT = %d\n", d->fd_in, d->fd_out);
	}
	return (tmp);
}

t_node	*open_doubleout(t_data *d, t_node *node)
{
	t_node *tmp;

	tmp = node;
	if (node->type == append)
	{
		delnode(&d->lst, node);
		node = node->next;
		if (d->fd_out)
			close(d->fd_out);
		d->fd_out = open(node->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		delnode(&d->lst, node);
		tmp = node;
		//printf("fdIN = %d, fdOUT = %d\n", d->fd_in, d->fd_out);
	}
	return (tmp);
}

t_node *scan_out_infiles(t_data *d, t_node *node)
{
	t_node *tmp;
	int		placed;

	placed = 0;
	while (node && node->type != piperino)
	{
		if ((node->type == cmd || node->type == opt
			|| node->type == builtin) && placed == 0)
		{
			placed = 1;
			tmp = node;
		}
		node = open_infile(d, node);
		node = open_outfile(d, node);
		node = open_doubleout(d, node);
		if (node)
			node = node->next;
	}
	if (node && node->type == piperino)
		d->scan_pipe = 1;
	node = tmp;
	return (node);
}
