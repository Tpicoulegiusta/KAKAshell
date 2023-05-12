/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:42:08 by sboetti           #+#    #+#             */
/*   Updated: 2023/04/07 13:26:20 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	lendst;

	if (dstsize == 0)
		return (ft_strlen(src));
	lendst = ft_strlen(dst);
	i = lendst;
	j = 0;
	if (dstsize <= lendst)
		return (ft_strlen(src) + dstsize);
	while (src[j] && i < (dstsize - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (lendst + ft_strlen(src));
}
/*if (!dst && dstsize == 0)
		return (ft_strlen(src));*/
