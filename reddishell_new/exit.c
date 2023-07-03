/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:45:11 by tpicoule          #+#    #+#             */
/*   Updated: 2023/07/03 16:59:29 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && n--)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}


int	ft_atoi(const char *str)
{
	int			i;
	int			x;
	long long	nb;

	i = 0;
	x = 1;
	nb = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			x = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (nb * x);
}

int	ft_built_exit(t_node *tmp)
{
	int	i;

	i = -1;
	if (!tmp)
		exit(127);
	while (tmp->str[++i])
	{
		if (tmp->str[i] == '|')
			break ;
		if (!ft_isdigit(tmp->str[i]))
		{
			printf("numeric argument required\n");
			exit (255);
		}
	}
	if ((tmp->type == piperino) || (tmp->next && tmp->next->type == piperino))
		return (1);//return 1
	exit(ft_atoi(tmp->str) % 256);
}
