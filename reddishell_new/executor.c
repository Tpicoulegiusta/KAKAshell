/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:15:47 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/19 16:54:46 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_builtins(char *str)
{
	if (ft_strcmp(str, "export") == 0 || ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
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
	if (!path)
		return (NULL);
	return (path);
}

char	*absolutepath(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (free(cmd), NULL);
}

char	*path_check(char *cmd, t_list *envlst)
{
	if (cmd[0] == '/')
		return (absolutepath(cmd));
	else
		return (getpath(cmd, envlst));
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

void	executor(t_list *lst, t_list *envlst, t_list *sort_envlst, char **envp)
{
	char	*argpath;
	char	**tabexec;
	t_node	*tmp;
	int		moves;
	int		pid;

	tmp = lst->first;
	while (tmp)
	{
		argpath = NULL;
		if (check_builtins(tmp->str) == 1)
		{
			export_unset(tmp, envlst, sort_envlst);
			check_env(envlst, tmp);
		}
		else
		{
			argpath = path_check(tmp->str, envlst);
			if (argpath)
			{
				moves = 0;
				while (tmp->next && tmp->next->str[0] == '-')
				{
					moves++;
					tmp = tmp->next;
				}
				tabexec = lst_to_tab(tmp, moves);
				pid = fork();
				if (pid == 0)
					execve(argpath, tabexec, envp);
				waitpid(pid, NULL, 0);
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
}
