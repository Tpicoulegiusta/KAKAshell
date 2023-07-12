/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:44:33 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/12 17:47:07 by rbulanad         ###   ########.fr       */
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
	ret = NULL;
	(void)cmd;
	while (allpaths[i])
	{
		ret = ft_pathjoin(allpaths[i], cmd);
		if (access(ret, F_OK) == 0)
			return (ret);
		free(ret);
		ret = NULL;
		i++;
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
	envcpy = NULL;
	path = NULL;
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
	//printf("path = %s\n", path);
	if (!path)
		return (NULL);
	return (path);
}

char	**lst_to_tab(t_node *node)
{
	char	*join;
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
