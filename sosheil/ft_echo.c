/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:47:44 by sboetti           #+#    #+#             */
/*   Updated: 2023/06/21 16:50:32 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fonction pour gerer plusieurs n// Envoyer l'adresse de option i pour gerer//
int	ft_option(t_node *tmp)
{
	int	i;

	i = -1;
	puts("tom");
	if (tmp->str[++i] == '-')
	{
		while (tmp->str[++i])
		{
			if (tmp->str[i] && tmp->str[i] != 'n')
				return (1);
		}
		return (0);
		puts("pere");
	}
	return (1);
}

int	ft_option2(t_node *tmp)
{
	int	i;

	i = 0;
	puts("tam");
	if (tmp->str[i] == '\"' || tmp->str[i] == '\"')
	{
		i++;
		if (tmp->str[i++] == '-')
		{
			while (tmp->str[i])
			{
				if (tmp->str[i] && tmp->str[i] != 'n')
					return (1);
			}
			return (0);
			puts("mere");
		}
	}
	return (1);
}

void	and_another_check(t_node *tmp)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if ((tmp->prev == NULL && !ft_strncmp(tmp->str, "echo", 4))
		|| (tmp->prev == NULL && !ft_strncmp(tmp->str, "\"echo\"", 6)))
	{
		puts("tagram");
		if ((tmp->next && !ft_option(tmp->next)) || (tmp->next && !ft_option2(tmp->next)))
		{
			option = 1;
			tmp = tmp->next;
			//si rien apres le -n ajouter condtion ou int//
		}
		printf("option === > %d\n", option);
		if (tmp->next)
			tmp = tmp->next;
		printf("tmp === > %s\n", tmp->str);
/*  		if (tmp->next )
		{
			while (tmp ||  ft_strcmp(tmp->str, "|") != 0)
			{
				while (tmp->str[i])
				{
					puts("maga");
					write(1, &tmp->str[i], 1);
					i++;
				}
				tmp = tmp->next;
			}
		} */
		//FAIRE MARCHER CETTE BOUCLE DE MERDE//
		if (option != 0)
		{
			write(1, "\n", 1);
		}
		//puts("caca");
	}
}
