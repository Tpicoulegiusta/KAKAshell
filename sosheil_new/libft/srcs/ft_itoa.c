/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:48:02 by sboetti           #+#    #+#             */
/*   Updated: 2023/04/07 12:27:25 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	chfr(int x, int i)
{
	if (x < 0)
		return (chfr(x * -1, 2));
	while (x >= 10)
	{
		x /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		x;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = malloc(sizeof(char) * chfr(n, 1) + 1);
	if (str == NULL)
		return (NULL);
	len = chfr(n, 1);
	x = n;
	str[len] = '\0';
	if (n < 0)
		x *= -1;
	while (--len >= 0)
	{
		str[len] = (x % 10) + 48;
		x /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
