/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/23 15:27:28 by sboetti          ###   ########.fr       */
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
//		if (lst->len > 2)
//			if (tmp->next->next->type == 1)
//				return ;
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

void	change_oldpwd(char *path, t_list *env)
{
	t_node	*tmp;

	tmp = find_node("OLDPWD", env);
	if (tmp->str)
		free(tmp->str);
	tmp->str = ft_ministrjoin("OLDPWD=", path);
	free(path);
	//envoyer a reddy l'export a modifier
}

void	change_pwd(t_list *env)
{
	t_node	*tmp;
	char	*s;

	s = getcwd(NULL, 0);
	tmp = find_node("PWD", env);
	if (tmp->str)
		free(tmp->str);
	tmp->str = ft_ministrjoin("PWD=", s);
	free(s);
	//envoyer a reddy l'export a modifier
}

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

int	cd_minus(char *path, char *str, t_list *env)
{
	t_node	*tmp;

	if (path[0] == '-' && !path[1])
	{
		tmp = find_node("OLDPWD", env);
		if (tmp && chdir(tmp->str) == -1)
		{
			printf("c'est quoi tout ca la\n");
			return (1);
		}
		else if (!tmp)
		{
			printf("OLDPWD qui le connait ??\n");
			return (1);
		}
		change_oldpwd(str, env);
		change_pwd(env);
	}
	return (0);
}

int	cd_dot(char *path, char *str)
{
	char	*pwd;

	if (path[0] == '.' && !path[1])
	{
		pwd = getcwd(NULL, 0);
		if (!ft_strncmp(path, ".", 2) && !pwd)
		{
			printf("C'est quoi ce bug de de golmon la\n");
			free(pwd);
			free(str);
			return (1);
		}
		else if (!pwd)
		{
			free(pwd);
			return (1);
		}
		free(pwd);
	}
	return (0);
}

void	another_check(t_list *envlst, t_node *tmp)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (tmp->next)
	{
		if (cd_tilde(tmp->next->str, s, envlst))
			return ;//(0);
		else if (cd_minus(tmp->next->str, s, envlst))
			return ;//(0);
		else if (cd_dot(tmp->next->str, s))
			return ;//(0);
		else if (chdir(tmp->next->str) == -1)
		{
			printf("Tu veux aller ou la ??\n");
			free(s);
			return ;// (1)
		}
	}
	if (tmp->next == NULL)
	{
		if (chdir(getenv("HOME")) == -1)
		{
			write(2, "Le HOME a disparu\n", 19);
			return ;
		}
		if (tmp->str)
			free(tmp->str);
		tmp->str = ft_strdup(getenv("HOME"));
	}
	change_pwd(envlst);
	change_oldpwd(s, envlst);
	return ;//(0);
}
