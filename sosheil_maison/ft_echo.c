/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:47:44 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/14 19:27:10 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fonction pour gerer plusieurs -n
t_node	*ft_option(t_node *tmp, int *option)
{
	int	i;
	int	ret;

	ret = 0;
	while (tmp && !ft_strncmp(tmp->str, "-n", 2))
	{
		i = 1;
		ret = 1;
		while (tmp->str[++i])
		{
			if (tmp->str[i] && tmp->str[i] != 'n')
			{
				ret = 2;
				break ;
			}
		}
		if (ret == 2)
			break ;
		tmp = tmp->next;
	}
	*option = ret;
	return (tmp);
}

void	filler(t_node *tmp)
{
	while (tmp && tmp->type != 1)
	{
		if (!ft_strcmp(tmp->str, "\'\'") || !ft_strcmp(tmp->str, "\"\""))
		{
			if (tmp->next && tmp->next->type != piperino)
				tmp->type = tmp->type;
			if (tmp->space == 1)
				printf(" ");
			tmp = tmp->next;
			continue ;
		}
		printf("%s", tmp->str);
		if (tmp->space == 1)
			printf(" ");
		tmp = tmp->next;
	}
	return ;
}

int	ft_echo(t_node *tmp)
{
	int	option;

	option = 0;
	if (tmp->space == 0 && tmp->next)
		return (printf("command not found\n"), 1);
	if (!tmp->next)
		return (write(1, "\n", 1), 0);
	if (tmp->next)
		tmp = ft_option(tmp->next, &option);
	filler(tmp);
	if (option == 0)
		printf("\n");
	return (0);
}
