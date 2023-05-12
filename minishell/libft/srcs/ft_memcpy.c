/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 08:19:20 by sboetti           #+#    #+#             */
/*   Updated: 2023/04/07 13:25:00 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*ptr;
	char		*ptr2;
	size_t		i;

	i = 0;
	ptr = (char *)src;
	ptr2 = (char *)dst;
	if (ptr == ptr2)
		return (dst);
	while (i < n)
	{
		ptr2[i] = ptr[i];
		i++;
	}
	return (dst);
}
