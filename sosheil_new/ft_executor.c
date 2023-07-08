/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:57:13 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/08 11:00:38 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*absolutepath(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (free(cmd), NULL);
}

char	*checkaccess(char **allpaths, char *cmd)
{
	char	*ret;
	int		i;

	i = 0;
	while (allpaths[i])
	{
		ret = ft_pathjoin(allpaths[i++], cmd);
		if (access(ret, F_OK) == 0)
			return (ret);
	}
	free(ret);
	return (NULL);
}

char	*getpath(char *cmd, t_list *envlst)
{
	t_node	*tmp;
	char	*path;
	char	*envcpy;
	char	**allpaths;

	tmp = envlst->first;
	while (tmp)
	{
		if (tmp->str[0] == 'P' && tmp->str[1] == 'A'
			&& tmp->str[2] == 'T' && tmp->str[3] == 'H')
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (0);
	envcpy = substr2(tmp->str, 5, ft_strlen(tmp->str));
	allpaths = ft_split(envcpy, ':');
	path = checkaccess(allpaths, cmd);
	printf("path = %s\n", path);
	if (!path)
		return (NULL);
	return (path);
}

char	**lst_to_tab(t_node *node)
{
	char 	*join;
	char	**ret;

	join = NULL;
	while (node && node->type != piperino)
	{
		join = joinfree(join, node->str);
		join = joinfree2(join, ' ');
		node = node->next;
	}
	ret = ft_split(join, ' ');
	return (free(join), ret);
}

char	*path_check(char *cmd, t_list *envlst)
{
	if (cmd[0] == '/')
		return (absolutepath(cmd));
	else
		return (getpath(cmd, envlst));
}

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

void	close_fds(t_data *d)
{
	if (d->fd_in)
		close(d->fd_in);
	if (d->fd_out)
		close(d->fd_out);
}

void	wait_for_pids(t_data *d)
{
	int	i;

	i = 0;
	while (d->pid[i])
		waitpid(d->pid[i++], NULL, 0);
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

int	execute(t_data *d, t_node *node, int builtin)
{
	d->argpath = path_check(node->str, &d->envlst);
	if (builtin)
	{
		if (!ft_strcmp("cd", node->str))
			return (another_check(&(d->envlst), node));
		if (!ft_strcmp("exit", node->str))
			return (ft_built_exit(node));
		if (ft_strcmp(node->str, "export") == 0 && node->next
			&& node->next->type != piperino)
			return (1);
		if (ft_strcmp(node->str, "unset") == 0)
			return (1);
	}
	if (d->argpath || builtin)
	{
		d->tabexec = lst_to_tab(node);
		d->pid[d->i] = fork();
		if (d->pid[d->i] == 0)
		{
			if (check_fds(d->fd_in, d->fd_out) == 1)
				exit (1);
			if (builtin)
			{
				free(d->argpath);
				freetab(d->tabexec);
				check_env(&d->envlst, node);
				export_unset(node, &d->envlst, &d->sort_env);
				exit(0);
			}
			else
				execve(d->argpath, d->tabexec, d->envtab);
		}
	}
	return (0);
}

int	execute_pipes(t_data *d, t_node *node, int builtin)
{
	d->argpath = path_check(node->str, &d->envlst);
	if (builtin)
	{
		if (!ft_strcmp("cd", node->str))
			return (another_check(&(d->envlst), node));
		if (!ft_strcmp("exit", node->str))
			return (ft_built_exit(node));
		if (ft_strcmp(node->str, "unset") == 0)
			return (1);
	}
	if (d->argpath || builtin)
	{
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
			if (builtin)
			{
				free(d->argpath);
				freetab(d->tabexec);
				check_env(&d->envlst, node);
				if (ft_strcmp(node->str, "export") == 0 && node->next
					&& node->next->type != piperino)
					exit (1);
				export_unset(node, &d->envlst, &d->sort_env);
				exit(0);
			}
			else
				execve(d->argpath, d->tabexec, d->envtab);
		}
		close(d->fd[1]);
		dup2(d->fd[0], STDIN_FILENO);
		close(d->fd[0]);
	}
	return (0);
}

void	executor(t_data *d)
{
	t_node	*node;
	int		pipes;
	int		builtin;

	d->argpath = NULL;
	d->i = 0;
	builtin = 0;
	d->pid = malloc (sizeof(pid_t) * (pipe_count(&d->lst) + 1));
	init_fds(d);
	pipes = pipe_count(&d->lst);
	node = d->lst.first;
	while (node)
	{
		builtin = is_builtin(node->str);
		if (scan_out_infiles(d, node) == 1)
		{
			if (execute_pipes(d, node, builtin) == 1)
			{
				check_env(&d->envlst, node);
				export_unset(node, &d->envlst, &d->sort_env);
			}
		}
		else
		{
			if (execute(d, node, builtin) == 1)
			{
				check_env(&d->envlst, node);
				export_unset(node, &d->envlst, &d->sort_env);
			}
		}
		close_fds(d);
		while (node && node->type != piperino)
			node = node->next;
		if (node)
			node = node->next;
		d->i++;
	}
	dup2(d->sfd_in, STDIN_FILENO);
	wait_for_pids(d);
	// free pid maybe

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
	printf("after scan = [%s]\n", test);
}
