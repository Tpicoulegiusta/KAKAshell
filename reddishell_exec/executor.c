/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:59:05 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/13 18:45:51 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			close(d->fd[0]);
			dup2(d->fd[1], STDOUT_FILENO);
			close(d->fd[1]);
		}
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

void	enter_the_heredoc(t_data *d, char *limit, int i)
{
	char	*line;

	line = NULL;
	d->stock_hd = NULL;
	d->fd_hd[i] = malloc(sizeof(int) * 2);
	pipe(d->fd_hd[i]);
	while(1)
	{
		line = readline("> ");
		if (ft_strcmp(line, limit) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, d->fd_hd[i][1]);
		ft_putchar_fd('\n', d->fd_hd[i][1]);
	}
	close(d->fd_hd[i][1]);
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

void	executor(t_data *d)
{
	t_node	*node;
	int		numpipe;

	d->argpath = NULL;
	d->i_pid = 0;
	numpipe = 0;
	d->builtin = 0;
	d->pid = malloc (sizeof(pid_t) * (pipe_count(d) + 1)); //sorcellerie, pipe_count malloc pour le tableau de fd_hd aswell
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
	//dup2(d->sfd_out, STDOUT_FILENO);
	//free pid maybe

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
