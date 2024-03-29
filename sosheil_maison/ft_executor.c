/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:57:13 by sboetti           #+#    #+#             */
/*   Updated: 2023/08/07 00:23:14 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_pids(t_data *d)
{
	int	i;

	i = 0;
	while (d->pid[i])
	{
		waitpid(d->pid[i], NULL, 0);
		i++;
	}
	free(d->pid);
	d->pid = NULL;
}

void	close_fds(t_data *d)
{
	if (d->fd_in)
		close(d->fd_in);
	if (d->fd_out)
		close(d->fd_out);
}

int	execute(t_data *d, t_node *node, int numpipe)
{
	d->argpath = path_check(node->str, &d->envlst);
	if (exec_builtin_checks(d->builtin, node) == 1)
		return (1);
	d->tabexec = lst_to_tab(node);
	d->pid[d->i_pid] = fork();
	if (d->pid[d->i_pid] == 0)
	{
		if (check_fds(d) == 1)
			exit (1);
		if (d->is_in)
			dup2(d->fd_in, STDIN_FILENO);
		if (d->is_out)
			dup2(d->fd_out, STDOUT_FILENO);
		if (d->fd_hd[numpipe][0])
		{
			dup2(d->fd_hd[numpipe][0], STDIN_FILENO);
			close(d->fd_hd[numpipe][0]);
		}
		child_func(d, node);
	}
	return (0);
}

int	execute_pipes(t_data *d, t_node *node, int numpipe)
{
	d->argpath = path_check(node->str, &d->envlst);
	if (exec_builtin_checks_pipe(d->builtin, node))
		return (1);
	d->tabexec = lst_to_tab(node);
	pipe(d->fd);
	d->pid[d->i_pid] = fork();
	if (d->pid[d->i_pid] == 0)
	{
		if (check_fds(d) == 1)
			exit (1);
		if (d->fd_hd[numpipe][0])
		{
			dup2(d->fd_hd[numpipe][0], STDIN_FILENO);
			close(d->fd_hd[numpipe][0]);
		}
		if (d->is_out)
			dup2(d->fd_out, STDOUT_FILENO);
		else
			ex_pipe_utils(d);
		child_func_pipes(d, node);
	}
	close(d->fd[1]);
	dup2(d->fd[0], STDIN_FILENO);
	close(d->fd[0]);
	return (0);
}

void	executor(t_data *d)
{
	t_node	*node;
	int		numpipe;

	d->argpath = NULL;
	d->i_pid = 0;
	numpipe = 0;
	d->builtin = 0;
	d->pid = malloc (sizeof(pid_t) * (pipe_count(d) + 1));
	init_fds(d);
	node = d->lst.first;
	node = scan_hd(d, node);
	while (node)
	{
		d->builtin = is_builtin_exec(node);
		node = executor_body(d, node, numpipe);
		close_fds(d);
		while (node && node->type != piperino)
			node = node->next;
		if (node)
			node = node->next;
		d->i_pid++;
		numpipe++;
	}
	dup2(d->sfd_in, STDIN_FILENO);
	wait_for_pids(d);
}
