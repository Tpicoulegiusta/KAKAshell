/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:15:47 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/16 15:40:55 by rbulanad         ###   ########.fr       */
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

char	**subtab(char **tab, int start, int end)
{
	char 	*join;
	char	**ret;

	join = NULL;
	if (start == end)
	{
		join = joinfree(join, tab[start]);
		ret = ft_split(join, ' ');
		return (free(join), ret);
	}
	while (start <= end)
	{
		join = joinfree(join, tab[start]);
		join = joinfree2(join, ' ');
		start++;
	}
	ret = ft_split(join, ' ');
	return (free(join), ret);
}

void	executor(char **tab, t_list *envlst, t_list *sort_envlst, char **envp)
{
	int		i;
	int		start;
	char	*argpath;
	char	**tabexec;
	int		pid;

	i = 0;
	while (tab[i])
	{
		argpath = NULL;
		if (check_builtins(tab[i]) == 1)
		{
			export_unset(tab, &i, envlst, sort_envlst);
			check_env(envlst, tab, &i);
		}
		else
		{
			argpath = getpath(tab[i], envlst);
			if (argpath)
			{
				start = i;
				while (tab[i + 1] && tab[i + 1][0] == '-')
					i++;
				tabexec = subtab(tab, start, i);
				pid = fork();
				if (pid == 0)
					execve(argpath, tabexec, envp);
				waitpid(pid, NULL, 0);
			}
		}
		if (tab[i])
			i++;
	}
}
