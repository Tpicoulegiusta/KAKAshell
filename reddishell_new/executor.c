/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:15:47 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/15 15:11:30 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_builtins(char *str)
{
	if (ft_strcmp(str, "export") == 0 || ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

void	executor(char **tab, t_list *envlst, t_list *sort_envlst)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (check_builtins(tab[i]) == 1)
		{
			export_unset(tab, &i, envlst, sort_envlst);
			check_env(envlst, tab, &i);
		}
		if (tab[i])
			i++;
	}
}
