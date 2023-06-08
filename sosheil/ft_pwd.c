/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:34:18 by tpicoule          #+#    #+#             */
/*   Updated: 2023/06/08 13:05:52 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_daeja(t_list *envlst)
{
	t_node	*tmp;

	if (envlst->pwd->str != NULL)
		free(envlst->pwd->str);
	envlst->pwd->str = ft_strdup(ft_ministrchr(envlst->pwd->str, '='));
	return ;
}

int	check_pwd(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'p' && str[i + 1] == 'w' && str[i + 2] == 'd'
		&& (str[i + 3] == ' ' || str[i + 3] == '\0'))
		return (0);
	return (1);
}

void	init_pwd(t_list *envlst)
{
	t_node	*env;

	env = envlst->first;
	envlst->pwd = malloc(sizeof(t_node));
	while (env)
	{
		if (ft_strncmp(env->str, "PWD", 3) == 0)
			envlst->pwd->str = ft_strdup(env->str);
		env = env->next;
	}
	ft_daeja(envlst);
	return ;
}

void	other_check(t_node *tmp, t_list *envlst)
{
	if (tmp->prev == NULL)
	{
		if (check_pwd(tmp->str) == 0)
		{
			if (envlst->pwd == NULL)
				init_pwd(envlst);
			free(tmp->str);
			tmp->str = ft_strdup(envlst->pwd->str);
		}
	}
	else if (tmp->prev->type == piperino && check_pwd(tmp->str) == 0)
	{
		if (envlst->pwd == NULL)
			init_pwd(envlst);
		free(tmp->str);
		tmp->str = ft_strdup(envlst->pwd->str);
	}
	return ;
}
