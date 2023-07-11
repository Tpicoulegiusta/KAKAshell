/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:15:47 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 11:53:51 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_to_list(t_list *envlst, char **envp)
{
	int		i;

	list_init(envlst);
	i = 0;
	while (envp[i])
		addnode(envlst, envp[i++]);
}
