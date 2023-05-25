/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:33:04 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/25 11:19:47 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	env_var(t_node *tmp, char *var, char **envp)
{
	int		i;
	char	*search;

	(void)tmp;
	(void)envp;
	search = NULL;
	i = 0;
	if (var[0] == '$')
	{
		search = substr2(var, 1, ft_strlen(var));
		tmp->venv = find_envline(envp, search);
		tmp->type = venv;
	}
}

void	parser(t_lst *lst, char **envp)
{
	t_node	*tmp;

	tmp = lst->first;
	while(tmp)
	{
		env_var(tmp, tmp->str, envp);
		tmp->path = getpath(envp, tmp->str);
		if (tmp->path != NULL)
			tmp->type = cmd;
		printf("path = %s &&& venv = %s &&& type = %d\n", tmp->path, tmp->venv, tmp->type);
		tmp = tmp->next;
	}
}