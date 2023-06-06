/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/06 17:06:37 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envpwd(t_list *envlst, t_node **oldpwd, t_node **pwd)
{
	t_node	*tmp;

	tmp = envlst->first;
	*oldpwd = malloc(sizeof(t_node));
	*pwd = malloc(sizeof(t_node));
	(*oldpwd)->str = NULL;
	(*pwd)->str = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "PWD", 3) == 0)
			*pwd = tmp;
		if (ft_strncmp(tmp->str, "OLDPWD", 6) == 0)
			*oldpwd = tmp;
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
	t_node	*oldpwd;
	t_node	*pwd;

	init_envpwd(envlst, &oldpwd, &pwd);
	if (tmp->str[0] == 'c' && tmp->str[1] == 'd'
		&& (tmp->str[2] == '\0' || tmp->str[2] == ' '))
	{
		if (lst->len > 2)
			if (tmp->next->next->type == piperino)
				return ;
		printf("oldpwd->str >>> %s\n", oldpwd->str);
		printf("pwd->str >>> %s\n", pwd->str);
		free(oldpwd->str);
		oldpwd->str = ft_strdup(pwd->str);
		printf("oldpwd->str >>> %s\n", oldpwd->str);
		if (tmp->next == NULL)
		{
			free(pwd->str);
			pwd->str = ft_strdup(getenv("HOME"));
		}
		else if (tmp->next->type == str)
			ft_do_cd(tmp, pwd);
		printf("pwd -> %s\n\n", pwd->str);
		free(tmp->str);
		tmp->str = ft_strdup(pwd->str);
		printf("tmp->str === %s\n\n", tmp->str);
	}
	return ;
}
