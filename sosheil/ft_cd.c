/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/26 14:09:00 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (cd_dot(tmp->next->str, s))
			return ;//(0);
		else if (chdir(tmp->next->str) == -1)
		{
			if (!tmp->next->str[1]
				&& (tmp->next->str[0] == '~' || tmp->next->str[0] == '-'))
				return ;// 1
			printf("Tu veux aller ou la ??\n");
			free(s);
			return ;// (1)
		}
	}
	if (chdir(getenv("HOME")) == -1)
	{
		write(2, "Le HOME a disparu\n", 19);
		return ;
	}
	if (tmp->str)
		free(tmp->str);
	tmp->str = ft_strdup(getenv("HOME"));
	change_pwd(envlst);
	change_oldpwd(s, envlst);
	return ;//(0);
}
