/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:48:54 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/10 11:48:01 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hexa(unsigned int i, int upper, int ptr)
{
	int		j;
	char	*base;

	j = 0;
	base = "0123456789abcdef";
	if (upper)
		base = "0123456789ABCDEF";
	if (ptr)
	{
		ft_putstr("0x");
		ptr -= ptr;
		j += 2;
	}
	if (i >= 16)
	{
		j += hexa(i / 16, upper, 0);
		j += hexa(i % 16, upper, 0);
	}
	if (i < 16)
		j += ft_putchar(base[i]);
	return (j);
}

int	hexa_p(unsigned long long i, int upper, int ptr)
{
	int		j;
	char	*base;

	j = 0;
	base = "0123456789abcdef";
	if (upper)
		base = "0123456789ABCDEF";
	if (ptr)
	{
		ft_putstr("0x");
		ptr -= ptr;
		j += 2;
	}
	if (i >= 16)
	{
		j += hexa_p(i / 16, upper, 0);
		j += hexa_p(i % 16, upper, 0);
	}
	if (i < 16)
		j += ft_putchar(base[i]);
	return (j);
}
