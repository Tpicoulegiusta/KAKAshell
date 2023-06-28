/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instant_err2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:10:41 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/24 16:31:40 by rbulanad         ###   ########.fr       */
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
