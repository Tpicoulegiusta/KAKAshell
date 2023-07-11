/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:59:05 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/11 19:56:08 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_data *d, t_node *node)
{
	d->argpath = path_check(node->str, &d->envlst);
	if (exec_builtin_checks(d->builtin, node) == 1)
		return (1);
	d->tabexec = lst_to_tab(node);
	d->pid[d->i] = fork();
	if (d->pid[d->i] == 0)
		child_func(d, node);
	return (0);
}

int	execute_pipes(t_data *d, t_node *node)
{
	d->argpath = path_check(node->str, &d->envlst);
	if (exec_builtin_checks_pipe(d->builtin, node))
		return (1);
	d->tabexec = lst_to_tab(node);
	pipe(d->fd);
	d->pid[d->i] = fork();
	if (d->pid[d->i] == 0)
	{
		close(d->fd[0]);
		dup2(d->fd[1], STDOUT_FILENO);
		close(d->fd[1]);
		if (check_fds(d->fd_in, d->fd_out) == 1)
			exit (1);
		child_func_pipes(d, node);
	}
	close(d->fd[1]);
	dup2(d->fd[0], STDIN_FILENO);
	close(d->fd[0]);
	return (0);
}

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

void	executor(t_data *d)
{
	t_node	*node;

	d->argpath = NULL;
	d->i = 0;
	d->builtin = 0;
	d->pid = malloc (sizeof(pid_t) * (pipe_count(&d->lst) + 1));
	init_fds(d);
	node = d->lst.first;
	while (node)
	{
		d->builtin = is_builtin(node->str);
		node = executor_body(d, node);
		close_fds(d);
		while (node && node->type != piperino)
			node = node->next;
		if (node)
			node = node->next;
		d->i++;
	}
	dup2(d->sfd_in, STDIN_FILENO);
	wait_for_pids(d);
	//free pid maybe
/*
////////////////////////
	node = d->lst.first;

	t_node *tmp;
	while (node)
	{
		if (node->type == in)
		{
			delnode(&d->lst, node);
			node = node->next;
			delnode(&d->lst, node);
			node = node->next;
			tmp = node;
		}
		if (node)
			node = node->next;
	}
	node = tmp;
	node = d->lst.first;

	printf("%s\n", node->str);
/////////////////////
*/
/*
	///////////////// T E S T /////////////////
	char	*test = NULL;
	node = d->lst.first;
	while (node)
	{
		test = joinfree(test, node->str);
		if (node->space != 0)
			test = joinfree2(test, ' ');
		node = node->next;
	}
	printf("after scan = %s\n", test);
*/	
}
