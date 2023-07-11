/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:47:44 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/08 13:08:02 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fonction pour gerer plusieurs n// Envoyer l'adresse de option i pour gerer//
int	ft_option(t_node *tmp)
{
	int	i;

	i = 0;
	if (tmp->str[i] == '-')
	{
		while (tmp->str[++i])
		{
			if (tmp->str[i] && tmp->str[i] != 'n')
				return (1);
		}
		return (0);
	}
	return (1);
}

void	filler(t_node *tmp)
{
	while (tmp && tmp->type != 1)
	{
		printf("%s", tmp->str);
		if (tmp->space == 1)
			printf(" ");
		tmp = tmp->next;
	}
	return ;
}

int	ft_echo(t_node *tmp)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (!tmp->next)
		return (write(1, "\n", 1), 0);
	if (tmp->next && !ft_option(tmp->next))
	{
		if (tmp->next->next && tmp->next->space == 1)
			option = 1;
		tmp = tmp->next;
		if (!tmp->next)
			return (0);
	}
	if (tmp->next && tmp->space == 1)
		tmp = tmp->next;
	filler(tmp);
	if (option == 0)
		printf("\n");
	return (0);
}
