/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:15:47 by sboetti           #+#    #+#             */
/*   Updated: 2023/06/06 13:21:23 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	env_add(t_list *list, char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->envline = NULL;
	new->envline = joinfree(new->envline, str);
	if (list->envlast == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		list->envfirst = new;
		list->envlast = new;
	}
	else
	{
		list->last->next = new;
		new->prev = list->last;
		list->last = new;
		new->next = NULL;
	}
	list->len++;
}
*/
void	ft_env_to_list(t_list *envlst, char **envp)
{
	int		i;

	list_init(envlst);
	i = 0;
	while (envp[i])
		addnode(envlst, envp[i++]);
}
