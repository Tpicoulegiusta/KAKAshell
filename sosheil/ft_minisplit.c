/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:17:29 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/16 11:18:24 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strsplitdup(char *src, int min, int max)
{
	char	*str;
	int		i;

	i = max - min;
	str = malloc(sizeof(char) * (i + 1));
	i = 0;
	if (str == NULL)
		return (NULL);
	while (min < max)
		str[i++] = src[min++];
	str[i] = '\0';
	return (str);
}

static int	ischarset(char c, char charset)
{
	if (charset != '\0')
	{
		if (c == charset)
			return (1);
	}
	return (0);
}

static int	kuantanamo(char *str, char charset)
{
	int		i;
	int		mot;

	i = 0;
	mot = 0;
	while (str[i])
	{
		while (ischarset(str[i], charset) && str[i])
			i++;
		if (str[i])
			mot++;
		while (!ischarset(str[i], charset) && str[i])
			i++;
	}
	return (mot);
}

void	ft_ifquoted(char **tab, char *str, int *i, int *j)
{
	int	start;

	if (str[*i] == '\"' || str[*i] == '\'')
	{
		(*i)++;
		start = *i;
		while (str[*i] != '\"' && str[*i] != '\'')
			(*i)++;
		tab[*j] = ft_strsplitdup(str, start, (*i));
		printf("start = %d, i = %d\n", start, *i);
		printf("tabj = %s\n", tab[*j]);
		(*j)++;
		(*i)++;
	}
	return ;
}

char	**ft_minisplit(char *s, char c)
{
	int		i;
	int		j;
	int		start;
	char	**tab;

	tab = malloc(sizeof(char *) * (kuantanamo((char *)s, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		ft_ifquoted(tab, s, &i, &j);
		while (ischarset(s[i], c) && s[i])
			i++;
		start = i;
		while (!ischarset(s[i], c) && s[i])
			i++;
		if (start != i)
			tab[j++] = ft_strsplitdup((char *)s, start, i);
	}
	tab[j] = NULL;
	return (tab);
}

// int	main()
// {
// 	int		i = 0;
// 	char	*str;
// 	char	**tab;

// 	str = "   \"ls wc\" \'renaud ta soeur\' \"cou cou  \"   ";
// 	tab = ft_minisplit(str, ' ');
// 	while (tab[i])
// 	{
// 		printf("tab[%d] = %s\n", i, tab[i++]);
// 	}
// 	printf("%s\n", tab[i]);
// }
