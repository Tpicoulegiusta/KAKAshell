/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:17:29 by sboetti           #+#    #+#             */
/*   Updated: 2023/06/06 14:17:59 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substr2(char *s, int start, int end)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(((end - start + 1) * sizeof(char)));
	while (start < end)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_ministrrchr(char *s, char c)
{
	int		i;
	int		slash;

	i = 0;
	slash = -1;
	while (s[i])
	{
		if (s[i] == c)
			slash = i;
		i++;
	}
	if (slash == -1)
		return (0);
	if (slash == 0)
		return (ft_strdup("/"));
	return (substr2(s, 0, slash));
}
