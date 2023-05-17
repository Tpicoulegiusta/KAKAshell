/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2222.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:02:04 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/15 18:26:02 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t    ft_count_words(char *s, char c);
static char        **ft_cut_words(char **tabtab, char *s, char c);

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

size_t    *is_separator(char c, size_t count_quotes[2])
{
    if (c == '\"')
        count_quotes[0]++;
    if (c == '\'')
        count_quotes[1]++;
    return (count_quotes);
}

 char    **ft_quote_split(char *str, char separator)
{
    char    **arr_arr;

    if (!str)
    {
        arr_arr = malloc(sizeof(char) * 1);
        if (!arr_arr)
            return (0);
        arr_arr[0] = 0;
        return (arr_arr);
    }
    arr_arr = malloc(sizeof(char *) * (ft_count_words(str, separator) + 1));
    if (!arr_arr)
        return (0);
    arr_arr = ft_cut_words(arr_arr, str, separator);
    return (arr_arr);
}

//***
// * count_quotes[0]    =    singlequotes
// * count_quotes[1]    =    doublequotes
//***
static size_t    ft_count_words(char *str, char separator)
{
    size_t    i;
    size_t    k;
    size_t    count_quotes[2];

    k = 0;
    i = 0;
    count_quotes[0] = 0;
    count_quotes[1] = 0;
    if (str[i] == separator)
        i++;
    if (str[0] != separator || str[i + 1] == '\0')
        k++;
    while (str[i])
    {
        is_separator(str[i], count_quotes);
        if (str[i] == separator && str[i + 1] != separator && str[i + 1] != '\0'
            && (count_quotes[1] % 2) == 0 && (count_quotes[0] % 2) == 0)
            k++;
        i++;
    }
    if (str[0] == separator && k > 0)
        k++;
    return (k);
}

static char    **ft_cut_words(char **tabtab, char *str, char separator)
{
    size_t    i;
    size_t    j;
    size_t    x;
    size_t    count_quotes[2];

    i = 0;
    j = 0;
    x = 0;
    count_quotes[0] = 0;
    count_quotes[1] = 0;
    while (str[i])
    {
        while (str[i] == separator)
        {
            is_separator(str[i], count_quotes);
            i++;
        }
        j = i;
        if (str[i])
        {
            while ((str[i] != separator && str[i])
                || (count_quotes[0] % 2) != 0 || (count_quotes[1] % 2) != 0)
            {
                is_separator(str[i], count_quotes);
                i++;
            }
            tabtab[x] = substr2(str, j, i - j);
            x++;
        }
    }
    return (tabtab [x] = NULL, tabtab);
}
