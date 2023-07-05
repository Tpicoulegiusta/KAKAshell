/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:57:13 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/05 12:29:29 by sboetti          ###   ########.fr       */
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

int scan_out_infiles(t_data *d, t_node *node, t_list *lst)
{
	node = lst->first;
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

void	executor(t_data *d, char **envp)
{
	//fd_in for infiles
	//fd_out for outfiles
	//sfd_in is STDIN
	//sfd_out is STDOUT
	//prev_fd for pipes
	t_node	*node;
	t_node	*filenode;
	char	*argpath;
	char	**tabexec;
	int		pid;
	int		tagram;

	argpath = NULL;
	init_fds(d);
	node = d->lst.first;
	filenode = node;
	while (node)
	{
		tagram = 0;
		if (scan_out_infiles(d, filenode, &d->lst) == 1)// s'arrete a la premiere pipe, =1 means que stopped sur une pipe
			puts("YOHOHO");
		if (node->type == cmd)
			argpath = path_check(node->str, &d->envlst);
		//builtins ouistiti//
		if (builtins(d) == 0)
		{
			tagram = 1;
			break ;
		}
		else if (argpath && tagram != 1)
		{
			tabexec = lst_to_tab(node);// s'arrete a la premiere pipe
			pid = fork();
			if (pid == 0)
			{
				if (check_fds(d->fd_in, d->fd_out) == 1)
					exit (1);
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
	printf("after scan = [%s]\n", test);
}
