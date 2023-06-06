/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:58:37 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/06 13:58:41 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_to_lst(t_list *envlst, char **envp)
{
	int		i;

	lst_init(envlst);
	i = 0;
	while (envp[i])
		addnode(envlst, envp[i++]);
}
