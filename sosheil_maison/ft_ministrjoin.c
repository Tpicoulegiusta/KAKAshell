/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ministrjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:12:04 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 12:55:09 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	if (!s1)
		ft_strdup("");
	if (!s2)
		return (NULL);
	ret = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		ret[i] = s1[i];
	ret[i++] = '/';
	while (s2[++j])
		ret[i + j] = s2[j];
	ret[i + j] = '\0';
	return (ret);
}

char	*ft_strjoin2(char *s1, char c)
{
	char	*ret;
	int		i;

	if (c == 0 || !s1)
		return (NULL);
	ret = malloc ((ft_strlen(s1) + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	return (ret);
}

char	*ft_ministrjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	if (!s2 || !s1)
		return (NULL);
	ret = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		ret[i] = s1[i];
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

char	*joinfree(char *s1, char *s2)
{
	char	*ret;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	ret = ft_ministrjoin(s1, s2);
	free(s1);
	return (ret);
}

char	*joinfree2(char *s1, char c)
{
	char	*ret;

	if (!c)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	ret = ft_strjoin2(s1, c);
	free(s1);
	return (ret);
}
