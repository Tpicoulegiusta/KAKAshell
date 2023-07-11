/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilsexec3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:24:49 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 15:51:24 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(t_data *d)
{
	d->prev_fd = 0;
	d->fd_in = 0;
	d->fd_out = 0;
	d->sfd_in = dup(STDIN_FILENO);
	d->sfd_out = dup(STDOUT_FILENO);
}

int	open_infile(t_data *d, t_node *node)
{
	if (node->type == in)
	{
		delnode(&d->lst, node);
		node = node->next;
		if (d->fd_in)
			close(d->fd_in);
		d->fd_in = open(node->str, O_RDONLY, 0777);
		delnode(&d->lst, node);
		node = node->next;
		if (d->fd_in < 0)
			return (1);
		printf("fdIN = %d, fdOUT = %d\n", d->fd_in, d->fd_out);
	}
	return (0);
}

int	open_outfile(t_data *d, t_node *node)
{
	if (node->type == out)
	{
		delnode(&d->lst, node);
		node = node->next;
		if (d->fd_out)
			close(d->fd_out);
		d->fd_out = open(node->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		delnode(&d->lst, node);
		node = node->next;
		if (d->fd_in < 0)
			return (1);
		printf("fdIN = %d, fdOUT = %d\n", d->fd_in, d->fd_out);
	}
	return (0);
}

int	open_doubleout(t_data *d, t_node *node)
{
	if (node->type == append)
	{
		delnode(&d->lst, node);
		node = node->next;
		if (d->fd_out)
			close(d->fd_out);
		d->fd_out = open(node->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		delnode(&d->lst, node);
		node = node->next;
		if (d->fd_in < 0)
			return (1);
		printf("fdIN = %d, fdOUT = %d\n", d->fd_in, d->fd_out);
	}
	return (0);
}

int	scan_out_infiles(t_data *d, t_node *node)
{
	while (node && node->type != piperino)
	{
		if (open_infile(d, node) == 1)
			continue ;
		if (open_outfile(d, node) == 1)
			continue ;
		if (open_doubleout(d, node) == 1)
			continue ;
		if (node)
			node = node->next;
	}
	if (node)
		return (1);
	return (0);
}
