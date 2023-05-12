/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arguments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 09:35:05 by sboetti           #+#    #+#             */
/*   Updated: 2023/04/07 10:42:21 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_putu(unsigned int n, int *count)
{
	if (n < 0)
	{
		ft_printf_putchar_fd('-', 1, count);
		ft_printf_putnbr_fd(n * -1, 1, count);
	}
	else if (n > 9)
	{
		ft_printf_putnbr_fd(n / 10, 1, count);
		ft_printf_putnbr_fd(n % 10, 1, count);
	}
	else
		ft_printf_putchar_fd('0' + n, 1, count);
}

static void	ft_puthex(unsigned long n, char *base, int *count)
{
	unsigned int	size;

	size = ft_printf_strlen(base);
	if (n >= size)
	{
		ft_puthex(n / size, base, count);
		ft_puthex(n % size, base, count);
	}
	else
		ft_printf_putchar_fd(base[n], 1, count);
}

static void	ft_putadress(size_t arg, int *count)
{
	ft_printf_putstr_fd("0x", 1, count);
	ft_puthex(arg, "0123456789abcdef", count);
}

void	ft_arguments(char str, va_list arg, int *count)
{
	char	*vaa;

	if (str == 'c')
		ft_printf_putchar_fd(va_arg(arg, int), 1, count);
	else if (str == 's')
	{
		vaa = va_arg(arg, char *);
		if (!vaa)
			ft_printf_putstr_fd("(null)", 1, count);
		else
			ft_printf_putstr_fd(vaa, 1, count);
	}
	else if (str == 'p')
		ft_putadress(va_arg(arg, size_t), count);
	else if (str == 'i' || str == 'd')
		ft_printf_putnbr_fd(va_arg(arg, int), 1, count);
	else if (str == 'u')
		ft_putu(va_arg(arg, unsigned int), count);
	else if (str == 'x')
		ft_puthex(va_arg(arg, unsigned int), "0123456789abcdef", count);
	else if (str == 'X')
		ft_puthex(va_arg(arg, unsigned int), "0123456789ABCDEF", count);
	else if (str == '%')
		ft_printf_putchar_fd('%', 1, count);
}
