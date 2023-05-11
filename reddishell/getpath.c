/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:05:12 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/11 18:10:05 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	strfind(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == find[j])
			j++;
		if (find[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}


char *find_envline(char **envp)
{
	int	i;

	i = 0;
	while (strfind(envp[i], "PATH") == 0)
		i++;
	return (envp[i] + 5);
}

char	*getpath(char **envp, char *cmd)
{
	int	i;
	char *envline;
	char **pathtab;
	char *path;

	envline = find_envline(envp);
	pathtab = ft_split(envline, ':');
	i = 0;
	while (pathtab[i])
	{
		path = joinfree(pathtab[i], cmd, 0);
		if (access(path, F_OK) == 0)
		{
			freetab(pathtab, i);
			return (path);
		}
		free(path);
		i++;
	}
	return (free(pathtab), pathtab = NULL, NULL);
}
