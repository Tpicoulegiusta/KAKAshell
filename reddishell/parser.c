/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/24 17:52:09 by rbulanad         ###   ########.fr       */
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
		search = substr2(var, 1, len(var));
		tmp->venv = find_envline(envp, search);
		tmp->type = venv;
	}
}
void	parser(t_list *lst, char **envp)
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
