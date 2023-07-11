/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilsexec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:24:12 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 12:56:19 by sboetti          ###   ########.fr       */
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
	while (allpaths[i])
	{
		ret = ft_pathjoin(allpaths[i++], cmd);
		if (!ret)
			return (NULL);
		if (access(ret, F_OK) == 0)
		{
			freetabpath(allpaths);
			return (ret);
		}
		free(ret);
		ret = NULL;
	}
	freetabpath(allpaths);
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
	if (!tmp)
		return (NULL);
	envcpy = substr2(tmp->str, 5, ft_strlen(tmp->str));
	allpaths = ft_split(envcpy, ':');
	path = checkaccess(allpaths, cmd);
	free(envcpy);
	if (!path)
		return (free(path), NULL);
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
