/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:34:18 by tpicoule          #+#    #+#             */
/*   Updated: 2023/06/06 13:32:39 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pwd(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'p' && str[i + 1] == 'w' && str[i + 2] == 'd'
		&& (str[i + 3] == ' ' || str[i + 3] == '\0'))
		return (0);
	return (1);
}

void	other_check(t_node *tmp)	//FONCTION PRINCIPALE A RAJOUTER AU PARSER
{
	char	buffer[BUFFER_SIZE];

	if (getcwd(buffer, BUFFER_SIZE) == NULL)
		return ;
	if (tmp->prev == NULL)
	{
		if (check_pwd(tmp->str) == 0)
		{
			free(tmp->str);
			tmp->str = ft_strdup(getcwd(buffer, BUFFER_SIZE));
		}
	}
	else if (tmp->prev->type == piperino && check_pwd(tmp->str) == 0)
	{
		free(tmp->str);
		tmp->str = ft_strdup(getcwd(buffer, BUFFER_SIZE));
	}
	return ;
}
