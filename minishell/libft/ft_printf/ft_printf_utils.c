/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:45:30 by sboetti           #+#    #+#             */
/*   Updated: 2023/04/07 10:42:25 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_printf_putchar_fd(char c, int fd, int *count)
{
	write(fd, &c, 1);
	*count += 1;
}

void	ft_printf_putstr_fd(char *str, int fd, int *count)
{
	int	i;

	if (!str)
		return ;
	else
	{
		i = 0;
		while (str[i])
		{
			ft_printf_putchar_fd(str[i], fd, count);
			i++;
		}
	}
}

void	ft_printf_putnbr_fd(int n, int fd, int *count)
{
	if (n == -2147483648)
		ft_printf_putstr_fd("-2147483648", fd, count);
	else if (n < 0)
	{
		ft_printf_putchar_fd('-', fd, count);
		ft_printf_putnbr_fd(n * -1, fd, count);
	}
	else if (n > 9)
	{
		ft_printf_putnbr_fd(n / 10, fd, count);
		ft_printf_putnbr_fd(n % 10, fd, count);
	}
	else
		ft_printf_putchar_fd('0' + n, fd, count);
}

size_t	ft_printf_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
