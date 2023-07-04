/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:13:38 by sboetti           #+#    #+#             */
/*   Updated: 2023/04/07 13:26:50 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	result_len(const char *str, const char *set, int *start)
{
	int	end;

	end = ft_strlen(str);
	while (str[*start] && ft_strchr(set, str[*start]))
		*start = *start + 1;
	while (end > *start && ft_strchr(set, str[end - 1]))
		end--;
	return (end - *start);
}

char	*ft_strtrim(const char *str, const char *set)
{
	char	*result;
	int		i;
	int		j;

	if (!str || !set)
		return (NULL);
	i = 0;
	j = result_len(str, set, &i);
	result = ft_substr(str, i, j);
	if (result == NULL)
		return (NULL);
	return (result);
}
