/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:47:44 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/04 13:58:44 by sboetti          ###   ########.fr       */
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

int	and_another_check(t_node *tmp)
{
	//Faire grande boucle qui pacours les nodes un a un pour tcheck a la fin si il y a un espace ou non//
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (!tmp->next)
		return (0);//aucune idee
	if (tmp->next && !ft_option(tmp->next))
	{
		option = 1;
		tmp = tmp->next;
		if (!tmp->next)
			return (0);
	}
	if (tmp->next)
		tmp = tmp->next;
	printf("echo option ===> %d\n", option);
	printf("echo tmp ===> %s\n", tmp->str);
	while (tmp && tmp->type != 1)
	{
		printf("[%s]", tmp->str);
		if (tmp->space == 1)
			printf(" ");
		tmp = tmp->next;
	}
	if (option == 0)
		printf("\n");
	return (0);
}