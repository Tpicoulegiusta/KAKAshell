/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:31:08 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/09 15:36:33 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	strfind(char *str, char *find)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	(void) find;
// 	while (str[i])
// 	{
// 		j = 0;
// 		while (str[i + j] && find[j] && str[i + j] == find[j])
// 			j++;
// 		if (find[j] == '\0')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	*find_envline(char **envp, char *search)
// {
// 	int		i;
// 	int		j;
// 	char	*ret;

// 	i = 0;
// 	j = 0;
// 	ret = NULL;
// 	while (strfind(envp[i], search) == 0)
// 		i++;
// 	while (envp[i][j] != '=')
// 		j++;
// 	ret = substr2(envp[i], j + 1, ft_strlen(envp[i]));
// 	return (ret);
// }

// char	*getpath(char **envp, char *cmd)
// {
// 	int		i;
// 	char	*envline;
// 	char	**pathtab;
// 	char	*path;

// 	envline = find_envline(envp, "PATH");
// 	pathtab = ft_split(envline, ':');
// 	i = 0;
// 	while (pathtab[i])
// 	{
// 		path = ft_pathjoin(pathtab[i], cmd);
// 		if (access(path, F_OK) == 0)
// 		{
// 			freetab(pathtab);
// 			return (path);
// 		}
// 		free(path);
// 		i++;
// 	}
// 	return (free(pathtab), pathtab = NULL, NULL);
// }
