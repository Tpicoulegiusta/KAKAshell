/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freee.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:22:29 by sboetti           #+#    #+#             */
/*   Updated: 2023/06/01 12:10:17 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freetab(char **tab, int i)
{
	if (tab[i + 1] != NULL)
	{
		i++;
		while (tab[i])
			free(tab[i++]);
		free(tab);
		tab = NULL;
	}
}
/*
void	free_execve(t_data *data)
{
	int	i;

	i = 0;
	free(data->path);
	while (data->argexec[i])
		free(data->argexec[i++]);
	free(data->argexec);
	data->argexec = NULL;
}*/

void	freelst(t_list *lst)
{
	t_node	*tmp;
	t_node	*next;

	tmp = lst->first;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = next;
	}
	lst->len = 0;
}