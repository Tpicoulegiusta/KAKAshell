/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freee.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:22:29 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/12 14:22:59 by sboetti          ###   ########.fr       */
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
