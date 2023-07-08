/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:33:04 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/08 10:56:08 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//utilise 'search' pour trouver la bonne ligne d'env
int	ft_find(char *str, char *search)
{
	int	i;

	i = 0;
	if (!search)
		return (0);
	while (str[i] && search[i] && search[i] == str[i])
		i++;
	if (search[i] == '\0' && str[i] == '=')
		return (1);
	return (0);
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

void	more_tokens(t_list *lst, t_list *envlst)
{
	t_node	*tmp;

	tmp = lst->first;
	while (tmp)
	{
		if (tmp->type == in && tmp->next && tmp->next->type == in)
		{
			tmp = tmp->next;
			tmp->str = joinfree2(tmp->str, '<');
			tmp->type = eof;
			delnode(lst, tmp->prev);
		}
		if (tmp->type == out && tmp->next && tmp->next->type == out)
		{
			tmp = tmp->next;
			tmp->str = joinfree2(tmp->str, '>');
			tmp->type = append;
			delnode(lst, tmp->prev);
		}
		if (is_cmd(tmp->str, envlst) == 1)
			tmp->type = cmd;
		if (is_builtin(tmp->str) == 1)
			tmp->type = builtin;
		tmp = tmp->next;
	}
}

//no need de gerer $$, $1, $2, $3, $#, $! etc...
int	parser(t_list *lst, t_list *envlst)
{
	dollaz(lst, envlst);
	unquoter(lst);
	more_tokens(lst, envlst);
	if (syntax_checker(lst) == 1)
		return (1);
	return (0);
}
