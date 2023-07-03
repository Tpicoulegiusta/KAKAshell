/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:39:38 by tpicoule          #+#    #+#             */
/*   Updated: 2023/07/03 16:56:18 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * len(s1) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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

int	another_check(t_list *envlst, t_node *tmp)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (tmp->next)
	{
		if (cd_dot(tmp->next->str, s))
			return (0);//(0);
		else if (chdir(tmp->next->str) == -1)
		{
			if (!tmp->next->str[1]
				&& (tmp->next->str[0] == '~' || tmp->next->str[0] == '-'))
				return (1);// 1
			printf("Tu veux aller ou la ??\n");
			free(s);
			return (1);// (1)
		}
	}
	if (chdir(getenv("HOME")) == -1)
	{
		write(2, "Le HOME a disparu\n", 19);
		return (1);
	}
	if (tmp->str)
		free(tmp->str);
	tmp->str = ft_strdup(getenv("HOME"));
	change_pwd(envlst);
	change_oldpwd(s, envlst);
	return (0);//(0);
}
