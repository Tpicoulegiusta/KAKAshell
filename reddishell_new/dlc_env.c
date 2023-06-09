/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlc_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:23:28 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/09 11:17:57 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *envlst)
{
	t_node	*tmp;

	tmp = envlst->first;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

void	check_env(t_list *envlst, char *line)
{
	char	**tabline;
	
	tabline = ft_split(line, ' ');
	if (ft_strcmp(tabline[0], "env") == 0)
	{
		if (tabline[1])
			printf("ENV ERROR\n");
		else
			print_env(envlst);
	}
	freetab(tabline);
}
