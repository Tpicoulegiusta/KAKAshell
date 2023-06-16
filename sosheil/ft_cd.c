/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/16 15:33:24 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_shyvana(t_list *envlst)
// {
// 	if (envlst->pwd->str != NULL)
// 		free(envlst->pwd->str);
// 	envlst->pwd->str = ft_ministrchr(envlst->pwd->str, '=');
// 	if (envlst->oldpwd->str != NULL)
// 		free(envlst->oldpwd->str);
// 	envlst->oldpwd->str = ft_ministrchr(envlst->oldpwd->str, '=');
// 	return ;
// }

// void	init_envpwd(t_list *envlst)
// {
// 	t_node	*tmp;

// 	tmp = envlst->first;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->str, "PWD", 3) == 0)
// 		{
// 			if (envlst->pwd != NULL)
// 			{
// 				free(envlst->pwd->str);
// 				free(envlst->pwd);
// 			}
// 			envlst->pwd = tmp;
// 		}
// 		if (ft_strncmp(tmp->str, "OLDPWD", 6) == 0)
// 			envlst->oldpwd = tmp;
// 		tmp = tmp->next;
// 	}
// 	ft_shyvana(envlst);
// 	return ;
// }

// void	ft_do_cd(t_node *tmp, t_node *pwd)
// {
// 	char	*s;

// 	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
// 	if (ft_strcmp(tmp->next->str, ".") == 0)
// 		return ;
// 	else if (ft_strcmp(tmp->next->str, "..") == 0)
// 	{
// 		chdir("..");
// 		free(pwd->str);
// 		pwd->str = ft_strdup(getcwd(s, MAXPATHLEN));
// 	}
// 	else
// 	{
// 		chdir(tmp->next->str);
// 		free(pwd->str);
// 		pwd->str = ft_strdup(getcwd(s, MAXPATHLEN));
// 	}
// 	free(s);
// 	return ;
// }

// void	another_check(t_list *lst, t_list *envlst, t_node *tmp)
// {
// 	if (tmp->str[0] == 'c' && tmp->str[1] == 'd'
// 		&& (tmp->str[2] == '\0' || tmp->str[2] == ' '))
// 	{
// 		if (lst->len > 2)
// 			if (tmp->next->next->type == 1)
// 				return ;
// 		if (envlst->oldpwd == NULL || envlst->pwd == NULL)
// 			init_envpwd(envlst);
// 		if (envlst->oldpwd->str != NULL)
// 			free(envlst->oldpwd->str);
// 		envlst->oldpwd->str = ft_strdup(envlst->pwd->str);
// 		if (tmp->next == NULL)
// 		{
// 			chdir(getenv("HOME"));
// 			if (envlst->pwd->str != NULL)
// 				free(envlst->pwd->str);
// 			envlst->pwd->str = ft_strdup(getenv("HOME"));
// 		}
// 		else if (tmp->next->type == str)
// 			ft_do_cd(tmp, envlst->pwd);
// 		free(tmp->str);
// 		tmp->str = ft_strdup(envlst->pwd->str);
// 	}
// 	return ;
// }

int	cd_tilde(char *path, char *str, t_list *env)
{
	t_node	*tmp;

	if (!path || (path[0] == '~' && !path[1]))
	{
		tmp = find_node("HOME", env);
		if (chdir(path) == -1)
		{
			printf("c'est quoi tout ca la\n");
			return (1);
		}
		change_oldpwd(str, env);
		change_pwd(env);
	}
	return (0);
}

void	another_check(t_list *lst, t_list *envlst, t_node *tmp)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (cd_tilde(tmp->next->str, s, envlst))
		return (0);
	if (cd_minus(tmp->next->str, s, envlst))
		return (0);
	if (cd_dot(tmp->next->str, s, envlst))
		return (0);
	return (0);
}
