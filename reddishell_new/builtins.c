/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:42:18 by tpicoule          #+#    #+#             */
/*   Updated: 2023/07/03 16:47:37 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(t_data *d)
{
	t_node	*tmp;

	tmp = d->lst.first;
	if (!ft_strncmp("pwd", tmp->str, 3))
		return (other_check(tmp, &(d->envlst)));
	if (!ft_strncmp("cd", tmp->str, 2))
		return (another_check(&(d->envlst), tmp));
	if (!ft_strncmp("echo", tmp->str, 4))
		return (and_another_check(tmp));
	if (!ft_strncmp(tmp->str, "exit", 4))
		return (ft_built_exit(tmp->next));
	print_lst(&(d->lst));
	return (0);
}
