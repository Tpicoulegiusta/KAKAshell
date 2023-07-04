/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:06:07 by sboetti           #+#    #+#             */
/*   Updated: 2023/04/07 13:25:03 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ptr;
	const char	*ptr2;
	size_t		i;

	ptr = dst;
	ptr2 = src;
	i = 0;
	if (ptr == ptr2)
		return (dst);
	if (dst > src)
	{
		while (i < len)
		{
			ptr[len - i - 1] = ptr2[len - i - 1];
			i++;
		}
	}
	else
	{
		while (i++ < len)
			ptr[i - 1] = ptr2[i - 1];
	}
	return (dst);
}
