/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:46:57 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/10 16:30:08 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
	{
		str[i] = src[min];
		i++;
		min++;
	}
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

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		start;
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (kuantanamo((char *)s, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (ischarset(s[i], c) && s[i])
			i++;
		start = i;
		while (!ischarset(s[i], c) && s[i])
			i++;
		if (start != i)
			tab[j++] = ft_strsplitdup(s, start, i);
	}
	tab[j] = NULL;
	return (tab);
}
