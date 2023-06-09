/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:15:15 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 18:17:09 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	whileonslash(char *str, int *i, int *start)
{
	while (str[*i])
	{
		if (str[*i] == '/')
			*start = *i;
		(*i)++;
	}
}
