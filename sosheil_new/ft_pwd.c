/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:34:18 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 17:03:46 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_node *tmp, t_list *env)
{
	char	*s;
	t_node	*node;

	s = getcwd(NULL, 0);
	if (tmp->next && tmp->next->type != piperino)
	{
		printf("c'est quoi ces arguments de GOLMON la\n");
		return (1);
	}
	if (s)
		printf("%s\n", s);
	else
	{
		node = find_node("PWD", env);
		if (node)
			printf("%s\n", node->str);
		return (1);
	}
	if (tmp->str)
		free(tmp->str);
	tmp->str = ft_strdup(s);
	free(s);
	return (0);
}
