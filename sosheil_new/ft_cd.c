/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/11 13:02:57 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_oldpwd(char *path, t_data *d)
{
	t_node	*tmp;

	tmp = find_node("OLDPWD", &(d->envlst));
	if (!tmp)
	{
		printf("OLDPWD is not in the env\n");
		return ;
	}
	if (tmp->str)
	{
		free(tmp->str);
		tmp->str = NULL;
	}
	tmp->str = ft_ministrjoin("OLDPWD=", path);
	if_else_double(&(d->sort_env), &(d->envlst), tmp->str);
	free(path);
	return ;
}

void	change_pwd(t_data *d)
{
	t_node	*tmp;
	char	*s;

	s = getcwd(NULL, 0);
	tmp = find_node("PWD", &(d->envlst));
	if (!tmp)
	{
		printf("PWD is not in the env\n");
		return ;
	}
	if (tmp->str)
		free(tmp->str);
	tmp->str = ft_ministrjoin("PWD=", s);
	if_else_double(&(d->sort_env), &(d->envlst), tmp->str);
	free(s);
	return ;
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

int	ft_cd(t_data *d, t_node *tmp)
{
	char	*s;

	s = NULL;
	if (ft_strcmp(tmp->str, "cd") == 0)
	{
		s = getcwd(NULL, 0);
		if (tmp->next)
		{
			if (cd_dot(tmp->next->str, s))
				return (0);
			else if (chdir(tmp->next->str) == -1)
			{
				if (!tmp->next->str[1]
					&& (tmp->next->str[0] == '~' || tmp->next->str[0] == '-'))
					return (1);
				return (write(2, "Tu veux aller ou la ??\n", 23), free(s), 1);
			}
		}
		else if (chdir(getenv("HOME")) == -1)
			return (write(2, "Le HOME a disparu\n", 19), 1);
		change_pwd(d);
		change_oldpwd(s, d);
	}
	return (0);
}
