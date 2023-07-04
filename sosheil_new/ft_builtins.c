/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:21:27 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/04 15:02:51 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(t_data *d)
{
	t_node	*tmp;

	tmp = d->lst.first;
	print_lst(&(d->lst));
	if (!ft_strncmp("pwd", tmp->str, 3))
		return (other_check(tmp, &(d->envlst)));
	if (!ft_strncmp("cd", tmp->str, 2))
		return (another_check(&(d->envlst), tmp));
	if (!ft_strncmp("echo", tmp->str, 4))
		return (and_another_check(tmp));
	if (!ft_strncmp(tmp->str, "exit", 4))
		return (ft_built_exit(tmp->next));
	return (0);
}
