/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportutils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:05:50 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 17:10:47 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	sort_lst(t_list *lst)
{
	t_list	tmplst;
	t_node	*tmp;
	t_node	*tmp2;
	int		len;

	len = lst->len;
	list_init(&tmplst);
	while (len != 0)
	{
		if (!lst->first)
			break ;
		tmp = lst->first;
		tmp2 = tmp;
		while (tmp)
		{
			if (ft_strcmp(tmp->str, tmp2->str) < 0)
				tmp2 = tmp;
			tmp = tmp->next;
		}
		addnode(&tmplst, tmp2->str);
		delnode(lst, tmp2);
		len--;
	}
	tmp = tmplst.first;
	while (tmp)
	{
		addnode(lst, tmp->str);
		tmp = tmp->next;
	}
	freelist(&tmplst);
}

int	spe_char_exp_uns(char c)
{
	if ((c >= 37 && c <= 59)
		|| c == '=' || c == '!' || c == '?'
		|| c == '\"' || c == '#')
		return (1);
	return (0);
}

int	is_pipe_redir(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

char	**node_tab_setter(t_node *node)
{
	t_node	*tmp;
	char	*join;
	char	**tab;

	tmp = node;
	join = NULL;
	while (node && node->type != piperino)
		node = node->next;
	while (tmp && is_pipe_redir(tmp->str[0]) == 0)
	{
		join = joinfree(join, tmp->str);
		if (tmp->space == 1)
			join = joinfree2(join, ' ');
		tmp = tmp->next;
	}
	tab = ft_split(join, ' ');
	return (free(join), tab);
}
