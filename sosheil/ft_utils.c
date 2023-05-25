/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:17:29 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/25 11:26:25 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substr2(char *s, int start, int end)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(((end - start + 1) * sizeof(char)));
	while (start < end)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
