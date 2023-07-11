/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportutils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:47:14 by tpicoule          #+#    #+#             */
/*   Updated: 2023/07/11 17:51:25 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_else_double(t_list *sort_envlst, t_list *envlst, char *str)
{
	if (check_double(sort_envlst, str) == 1)
	{
		del_double(sort_envlst, str);
		addnode(sort_envlst, str);
		export_env(envlst, str);
	}
	else if (check_double(sort_envlst, str) == 0)
	{
		export_env(envlst, str);
		addnode(sort_envlst, str);
	}
}

void	search_and_del(t_list *envlst, t_list *sort_envlst, char *str)
{
	t_node	*tmp;
	char	*cutstr;

	tmp = envlst->first;
	while (tmp)
	{
		cutstr = NULL;
		cutstr = cutter(tmp->str);
		if (ft_strcmp(cutstr, str) == 0)
			delnode(envlst, tmp);
		tmp = tmp->next;
		free(cutstr);
	}
	tmp = sort_envlst->first;
	while (tmp)
	{
		cutstr = NULL;
		cutstr = cutter(tmp->str);
		if (ft_strcmp(cutstr, str) == 0)
			delnode(sort_envlst, tmp);
		tmp = tmp->next;
		free(cutstr);
	}
}
