/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:59:05 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/28 19:18:45 by rbulanad         ###   ########.fr       */
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
	envcpy = substr2(tmp->str, 5, len(tmp->str));
	allpaths = ft_split(envcpy, ':');
	path = checkaccess(allpaths, cmd);
	printf("path = %s\n", path);
	if (!path)
		return (NULL);
	return (path);
}

char	**lst_to_tab(t_node *node, int moves)
{
	char 	*join;
	char	**ret;

	join = NULL;
	if (moves == 0)
	{
		join = joinfree(join, node->str);
		ret = ft_split(join, ' ');
		return (free(join), ret);
	}
	while (moves >= 0)
	{
		join = joinfree(join, node->str);
		join = joinfree2(join, ' ');
		moves--;
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

void	scan_out_infiles(t_data *d, t_list *lst)
{
	t_node	*node;

	node = lst->first;
	while (node && node->next && node->next->type != piperino)
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
				break ;
			printf("fdIN = %d, fdOUT = %d\n", d->fd_in, d->fd_out);
			continue ;
		}
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
				break ;
			printf("fdIN = %d, fdOUT = %d\n", d->fd_in, d->fd_out);
			continue ;
		}
		if (node)
			node = node->next;
	}
}

int	is_redir_pipe(int type)
{
	if (type >= 1 && type <= 5)
		return (1);
	return (0);
}

void	executor(t_data *d, char **envp)
{
	//fd_in for infiles
	//fd_out for outfiles
	//sfd_in is STDIN
	//sfd_out is STDOUT
	//prev_fd for pipes
	t_node	*node;
	char	*argpath;
	char	**tabexec;
	int		moves;
	int		pid;

	argpath = NULL;
	init_fds(d);
	scan_out_infiles(d, &d->lst);
	node = d->lst.first;
	while (node)
	{
		argpath = path_check(node->str, &d->envlst);
		if (argpath)
		{
			moves = 0;
			while (node->next && is_redir_pipe(node->next->type) != 1)
			{
				moves++;
				node = node->next;
			}
			tabexec = lst_to_tab(node, moves);
			printf("tabexec %s\n", tabexec[1]);
			pid = fork();
			if (pid == 0)
			{
				if (d->fd_in < 0)
				{
					(printf("INFILE ERROR\n"));
					exit (1);
				}
				if (d->fd_in)
					dup2(d->fd_in, STDIN_FILENO);
				if (d->fd_out < 0)
				{
					(printf("OUTFILE ERROR\n"));
					exit (1);
				}
				if (d->fd_out)
					dup2(d->fd_out, STDOUT_FILENO);
				execve(argpath, tabexec, envp);
			}
		}
		node = node->next;
	}
	waitpid(pid, NULL, 0);

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
	printf("%s\n", test);
}


