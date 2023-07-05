/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:21:27 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/05 11:37:35 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(t_data *d)
{
	t_node	*tmp;

	tmp = d->lst.first;
	print_lst(&(d->lst));
	if (!ft_strncmp("pwd\0", tmp->str, 4))
		return (other_check(tmp, &(d->envlst)));
	if (!ft_strncmp("cd\0", tmp->str, 3))
		return (another_check(&(d->envlst), tmp));
	if (!ft_strncmp("echo\0", tmp->str, 5))
		return (and_another_check(tmp));
	if (!ft_strncmp("exit\0", tmp->str, 5))
		return (ft_built_exit(tmp));
	return (0);
}
