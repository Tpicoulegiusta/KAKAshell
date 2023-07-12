/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:53:51 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/12 14:04:08 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unquote(char *str)
{
	char	*ret;
	int		i;

	i = 1;
	ret = NULL;
	if (str[0] == '\"')
	{
		while (str[i] != '\"')
			ret = joinfree2(ret, str[i++]);
		return (free(str), str = NULL, ret);
	}
	if (str[0] == '\'')
	{
		while (str[i] != '\'')
			ret = joinfree2(ret, str[i++]);
		return (free(str), str = NULL, ret);
	}
	return (str);
}

void	unquoter(t_list *lst)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = lst->first;
	while (tmp)
	{
		if (tmp->type != venv)
			tmp->str = unquote(tmp->str);
		tmp = tmp->next;
		i++;
	}
}

int	is_cmd(char *str, t_list *envlst)
{
	int	start;
	int	i;

	i = 1;
	start = 0;
	if (str[0] == '/')
	{
		while (str[i])
		{
			if (str[i] == '/')
				start = i;
			i++;
		}
		if (absolutepath(substr2(str, start, i)) != NULL)
			return (1);
	}
	else
	{
		if (getpath(str, envlst) != NULL)
			return (1);
	}
	return (0);
}

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}
