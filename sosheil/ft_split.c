/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:48:08 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/10 10:07:28 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	countwrd(char *s, char c)
{	
	int		i;
	int		trigger;

	i = 0;
	trigger = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (i);
}

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

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	char	**tab;
	int		index;

	tab = malloc((countwrd(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= len(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == len(s)) && index >= 0)
		{
			tab[j++] = substr2(s, index, i);
			index = -1;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}
/*
#include <stdio.h>
int	main()
{
	char *str;
	char **tab;

	str = "            ";
	tab = ft_split(str, ' ');
	int i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i++]);
		write(1, ".\n", 2);
	}
	printf("%s\n", tab[i]);
}*/
