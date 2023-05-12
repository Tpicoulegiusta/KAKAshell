/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:31:08 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/12 14:34:02 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*find_envline(char **envp)
{
	int	i;

	i = 0;
	while (strfind(envp[i], "PATH") == 0)
		i++;
	return (envp[i] + 5);
}

char	*getpath(char **envp, char *cmd)
{
	int		i;
	char	*envline;
	char	**pathtab;
	char	*path;

	envline = find_envline(envp);
	pathtab = ft_split(envline, ':');
	i = 0;
	while (pathtab[i])
	{
		path = joinfree(pathtab[i], cmd);
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
