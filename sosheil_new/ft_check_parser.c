/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:49:01 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/05 10:40:26 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spe_char(char c)
{
	if ((c >= 32 && c <= 47) || c == '\'' || c == '\"' || c == '=')
		return (1);
	return (0);
}

char	*unquote(char *str)
{
	char	*ret;
	int		i;

	i = 1;
	ret = NULL;
	if (str[0] == '\"')
	{
		while (str[i] != '\"')
			ret = joinfree2(ret, str[i++]);
		return (free(str), str = NULL, ret);
	}
	if (str[0] == '\'')
	{
		while (str[i] != '\'')
			ret = joinfree2(ret, str[i++]);
		return (free(str), str = NULL, ret);
	}
	return (str);
}

int	syntax_checker(t_list *lst)
{
	t_node	*tmp;

	tmp = lst->first;
	while (tmp)
	{
		if ((tmp->type == in || tmp->type == out || tmp->type == append
				|| tmp->type == eof || tmp->type == piperino) && !tmp->next)
			return (printf("SYNTAX ERROR IN PARSER\n"), 1);
		tmp = tmp->next;
	}
	return (0);
}

void	unquoter(t_list *lst)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = lst->first;
	while (tmp)
	{
		if (tmp->type != venv)
			tmp->str = unquote(tmp->str);
		tmp = tmp->next;
		i++;
	}
}

int	is_space(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)
		{
			str = substr2(str, 0, i);
			return (1);
		}
		i++;
	}
	return (0);
}
