/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/07 18:13:12 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envpwd(t_list *envlst)
{
	t_node	*tmp;

	if (envlst->pwd == NULL)
		envlst->pwd = malloc(sizeof(t_node));
	envlst->oldpwd = malloc(sizeof(t_node));
	tmp = envlst->first;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "PWD", 3) == 0)
		{
			envlst->pwd = tmp;
		}
		if (ft_strncmp(tmp->str, "OLDPWD", 6) == 0)
			envlst->oldpwd = tmp;
		tmp = tmp->next;
	}
	return ;
}

void	ft_do_cd(t_node *tmp, t_node *pwd)
{
	if (ft_strcmp(tmp->next->str, ".") == 0)
		return ;
	else if (ft_strcmp(tmp->next->str, "..") == 0)
		pwd->str = ft_ministrrchr(pwd->str, '/');
	return ;
}

void	another_check(t_list *lst, t_list *envlst, t_node *tmp)
{
	if (tmp->str[0] == 'c' && tmp->str[1] == 'd'
		&& (tmp->str[2] == '\0' || tmp->str[2] == ' '))
	{
		if (lst->len > 2)
			if (tmp->next->next->type == piperino)
				return ;
		if (envlst->oldpwd == NULL || envlst->pwd == NULL)
			init_envpwd(envlst);
		if (envlst->oldpwd->str != NULL)
			free(envlst->oldpwd->str);
		printf("Oldpwd->str >>> %s\n", envlst->oldpwd->str);
		printf("pwd->str >>> %s\n", envlst->pwd->str);
		envlst->oldpwd->str = ft_strdup(envlst->pwd->str);
			puts("coucou");
		printf("NEW oldpwd->str >>> %s\n", envlst->oldpwd->str);
		if (tmp->next == NULL)
		{
			free(envlst->pwd->str);
			envlst->pwd->str = ft_strdup(getenv("HOME"));
		}
		else if (tmp->next->type == str)
			ft_do_cd(tmp, envlst->pwd);
		printf("pwd -> %s\n\n", envlst->pwd->str);
		free(tmp->str);
		tmp->str = ft_strdup(envlst->pwd->str);
		printf("tmp->str === %s\n\n", tmp->str);
	}
	return ;
}
