/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:00:08 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 17:49:28 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_env(t_list *envlst, char	*str)
{
	if (ft_find_char(str, '=') == 1)
	{
		if (check_double(envlst, str) == 1)
		{
			del_double(envlst, str);
			addnode(envlst, str);
		}
		else if (check_double(envlst, str) == 0)
			addnode(envlst, str);
	}
}

int	ft_export(t_node *node, t_list *envlst, t_list *sort_envlst)
{
	char	**tmptab;
	int		i;

	if (!node->next || (node->next && node->next->type == piperino))
	{
		sort_lst(sort_envlst);
		print_export(sort_envlst);
		return (0);
	}
	tmptab = node_tab_setter(node);
	i = 1;
	while (tmptab[i])
	{
		if (spe_char_exp_uns(tmptab[i][0]) == 1)
		{
			printf("EXPORT SYNTAX ERR\n");
			i++;
		}
		if (tmptab[i])
			if_else_double(sort_envlst, envlst, tmptab[i++]);
	}
	free(tmptab);
	return (1);
}

void	ft_unset(t_node *node, t_list *envlst, t_list *sort_envlst)
{
	if (!node->next)
		return ;
	node = node->next;
	while (node && is_pipe_redir(node->str[0]) == 0)
	{
		if (spe_char_exp_uns(node->str[0]) == 1)
		{
			printf("UNSET SYNTAX ERR\n");
			node = node->next;
			continue ;
		}
		if (!node)
			break ;
		search_and_del(envlst, sort_envlst, node->str);
		node = node->next;
	}
}

int	export_unset(t_node *node, t_list *envlst, t_list *sort_envlst)
{
	int	export;

	if (ft_strcmp(node->str, "export") == 0)
	{
		export = ft_export(node, envlst, sort_envlst);
		return (export);
	}
	if (ft_strcmp(node->str, "unset") == 0)
	{
		ft_unset(node, envlst, sort_envlst);
		return (1);
	}
	return (0);
}
