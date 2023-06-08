/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/08 15:57:01 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shyvana(t_list *envlst)
{
	t_node	*tmp;

	if (envlst->pwd->str != NULL)
		free(envlst->pwd->str);
	envlst->pwd->str = ft_strdup(ft_ministrchr(envlst->pwd->str, '='));
	if (envlst->oldpwd->str != NULL)
		free(envlst->oldpwd->str);
	envlst->oldpwd->str = ft_strdup(ft_ministrchr(envlst->oldpwd->str, '='));
	return ;
}

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
			system("leaks minishell");
		}
		if (ft_strncmp(tmp->str, "OLDPWD", 6) == 0)
			envlst->oldpwd = tmp;
		tmp = tmp->next;
	}
	ft_shyvana(envlst);
	return ;
}

void	ft_do_cd(t_node *tmp, t_node *pwd)
{
	char	s[BUFFER_SIZE];

	if (ft_strcmp(tmp->next->str, ".") == 0)
		return ;
	else if (ft_strcmp(tmp->next->str, "..") == 0)
		pwd->str = ft_ministrrchr(pwd->str, '/');
	else
	{
		chdir(tmp->next->str);
		pwd->str = ft_strdup(getcwd(s, BUFFER_SIZE));
		//free(pwd->str);
		//pwd->str = ft_strdup(s);
		printf("LE PWD->STR est devenu %s\n", pwd->str);
	}
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
		//printf("Oldpwd->str >>> %s\n", envlst->oldpwd->str);
		//printf("pwd->str >>> %s\n", envlst->pwd->str);
		envlst->oldpwd->str = ft_strdup(envlst->pwd->str);
		//printf("NEW oldpwd->str >>> %s\n", envlst->oldpwd->str);
		if (tmp->next == NULL)
		{
			free(envlst->pwd->str);
			envlst->pwd->str = ft_strdup(getenv("HOME"));
		}
		else if (tmp->next->type == str)
			ft_do_cd(tmp, envlst->pwd);
		free(tmp->str);
		tmp->str = ft_strdup(envlst->pwd->str);
	}
	return ;
}
