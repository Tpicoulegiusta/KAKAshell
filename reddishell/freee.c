/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freee.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:23:43 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/12 12:31:11 by rbulanad         ###   ########.fr       */
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
	t_tok	*current;
	t_tok	*next;

	current = lst->first;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(lst);
}