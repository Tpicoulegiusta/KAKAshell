/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:17:29 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/12 16:07:36 by sboetti          ###   ########.fr       */
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

void	ft_ifquoted(char **tab, char *str, int *i, int *j)
{
	int	start;

	if (str[*i] == '\"' || str[*i] == '\'')
	{
		start = *i;
		start++;
		(*i)++;
		while (str[*i] != '\"' && str[*i] != '\'')
			(*i)++;
		(*i) += 1;
		tab[*j] = substr2(str, start, (*i) - 1);
		(*j)++;
	}
	return ;
}

char	**ft_minisplit(char *s, char c)
{
	int		i;
	int		j;
	char	**tab;
	int		index;

	tab = malloc((countwrd(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = -1;
	j = 0;
	index = -1;
	while (++i <= ft_strlen(s))
	{
		ft_ifquoted(tab, s, &i, &j);
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			tab[j++] = substr2(s, index, i);
			index = -1;
		}
	}
	tab[j] = NULL;
	return (tab);
}

// int	main()
// {
// 	int		i = 0;
// 	char	*str;
// 	char	**tab;

// 	str = "   \"ls wc\"   \'          renaud ta soeur\'  \"cou cou     \"      ";
// 	tab = ft_minisplit(str, ' ');
// 	while (tab[i])
// 	{
// 		printf("tab[%d] = %s\n", i, tab[i++]);
// 	}
// 	printf("%s\n", tab[i]);
// }
