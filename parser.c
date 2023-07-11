/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/11 17:25:05 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spe_char(char c)
{
	if ((c >= 32 && c <= 47) || c == '\'' || c == '\"' || c == '=')
		return (1);
	return (0);
}

//utilise 'search' pour trouver la bonne ligne d'env
int	ft_find(char *str, char *search)
{
	int	i;

	i = 0;
	if (!search)
		return (0);
	while (str[i] && search[i] && search[i] == str[i])
		i++;
	if (search[i] == '\0' && str[i] == '=')
		return (1);
	return (0);
}

void	more_tokens(t_list *lst, t_list *envlst)
{
	t_node	*tmp;

	tmp = lst->first;
	while (tmp)
	{
		if (tmp->type == in && tmp->next && tmp->next->type == in)
		{
			tmp = tmp->next;
			tmp->str = joinfree2(tmp->str, '<');
			tmp->type = eof;
			delnode(lst, tmp->prev);
		}
		if (tmp->type == out && tmp->next && tmp->next->type == out)
		{
			tmp = tmp->next;
			tmp->str = joinfree2(tmp->str, '>');
			tmp->type = append;
			delnode(lst, tmp->prev);
		}
		if (is_cmd(tmp->str, envlst) == 1)
			tmp->type = cmd;
		if (is_builtin(tmp->str) == 1)
			tmp->type = builtin;
		if (tmp)
			tmp = tmp->next;
	}
}

int	syntax_checker(t_list *lst)
{
	t_node	*tmp;

	tmp = lst->first;
	while (tmp)
	{
		if ((tmp->type == in || tmp->type == out || tmp->type == append
				|| tmp->type == eof) && !tmp->next)
			return (printf("SYNTAX ERROR IN PARSER\n"), 1);
		if (tmp->type == piperino && (!tmp->prev || !tmp->next))
			return (printf("SYNTAX ERROR NEAR UNEXPECTED TOKEN '|'\n"), 1);
		tmp = tmp->next;
	}
	return (0);
}

//no need de gerer $$, $1, $2, $3, $#, $! etc...
int	parser(t_list *lst, t_list *envlst)
{
	dollaz(lst, envlst);
	unquoter(lst);
	more_tokens(lst, envlst);
	if (syntax_checker(lst) == 1)
		return (1);
	return (0);
}
