/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:05:12 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/24 18:22:48 by rbulanad         ###   ########.fr       */
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
	(void) find;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && find[j] && str[i + j] == find[j])
			j++;
		if (find[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*find_envline(char **envp, char *search)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = NULL;
	while (strfind(envp[i], search) == 0) // <-- CACA SIGSEV
		i++;
	while (envp[i][j] != '=')
		j++;
	ret = substr2(envp[i], j + 1, len(envp[i]));
	return (ret);
}

char	*getpath(char **envp, char *cmd)
{
	int		i;
	char	*envline;
	char	**pathtab;
	char	*path;

	envline = find_envline(envp, "PATH");
	pathtab = ft_split(envline, ':');
	i = 0;
	while (pathtab[i])
	{
		path = ft_pathjoin(pathtab[i], cmd);
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
