/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:47:44 by sboetti           #+#    #+#             */
/*   Updated: 2023/06/30 15:53:06 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fonction pour gerer plusieurs n// Envoyer l'adresse de option i pour gerer//
int	ft_option(t_node *tmp)
{
	int	i;

	i = 0;
	// puts("tom");
	if (tmp->str[i] == '-')
	{
		while (tmp->str[++i])
		{
			if (tmp->str[i] && tmp->str[i] != 'n')
				return (1);
		}
		return (0);
		// puts("pere");
	}
	return (1);
}

void	and_another_check(t_node *tmp)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if ((!ft_strncmp(tmp->str, "echo", 4))
		|| ft_strncmp(tmp->str, "\"echo\"", 6))
	{
		// puts("tagram");
		if (!tmp->next)
			return ;//aucune idee
		if (tmp->next && !ft_option(tmp->next))
		{
			option = 1;
			tmp = tmp->next;
			if (!tmp->next)
				return ;
		}
		if (tmp->next)
			tmp = tmp->next;
		printf("option ===> %d\n", option);
		printf("tmp ===> %s\n", tmp->str);
		if (option == 1)
		{
			while (tmp && tmp->type != 1)
			{
				printf("%s", tmp->str);// a modifier imperativement
				tmp = tmp->next;
			}
		}
		else
		{
			while (tmp && tmp->type != 1)
			{
				printf("%s", tmp->str);// a modifier imperativement
				tmp = tmp->next;
			}
			printf("\n");
		}
		// puts("MERREEE");
	}
}
 