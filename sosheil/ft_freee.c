/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freee.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:22:29 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/26 11:13:38 by sboetti          ###   ########.fr       */
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

void	freelst(t_lst *lst)
{
	t_node	*current;
	t_node	*next;

	current = lst->first;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	lst->len = 0;
}
