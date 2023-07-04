/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:32:28 by sboetti           #+#    #+#             */
/*   Updated: 2023/04/07 13:25:49 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_sort_int_tab(int *tab, int size)
{
	int	tri;
	int	i;
	int	temp;

	i = 0;
	tri = 0;
	while (tri == 0)
	{
		tri = 1;
		while (i < size - 1)
		{
			if (tab[i] > tab[i + 1])
			{
				tri = 0;
				temp = tab [i];
				tab[i] = tab[i + 1];
				tab[i + 1] = temp;
				i = 0;
			}
			else
				i++;
		}
	}
}
