/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:15:43 by sboetti           #+#    #+#             */
/*   Updated: 2023/04/07 13:26:46 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	a;
	int		i;
	int		ok;

	i = 0;
	a = (char)c;
	ok = -1;
	if (!a)
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == a)
			ok = i;
		i++;
	}
	if (ok == -1)
		return (0);
	return ((char *)&s[ok]);
}
