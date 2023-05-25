/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instant_error2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:12:14 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/25 10:13:42 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	semi(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		inside_quotes(line, &i);
		if (line[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

int	backslash(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		inside_quotes(line, &i);
		if (line[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}
