/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:33:02 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 18:10:11 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	tokenizer(t_list *lst)
{
	t_node	*tmp;

	if (!lst->first)
		return ;
	tmp = lst->first;
	while (tmp)
	{
		if (dollar_check(tmp->str) == 1)
			tmp->type = venv;
		else if (tmp->str[0] == '|' && !tmp->str[1])
			tmp->type = piperino;
		else if (tmp->str[0] == '>' && !tmp->str[1])
			tmp->type = out;
		else if (tmp->str[0] == '<' && !tmp->str[1])
			tmp->type = in;
		tmp = tmp->next;
	}
}

int	lexer_checks(t_list *lst, char *line, char **copy, int *i)
{
	if (quoted(lst, line, copy, i) == 1)
		return (1);
	if (check_32(lst, line[*i], copy) == 1)
		return (1);
	if (check_spe(lst, line, *i, copy) == 1)
		return (1);
	return (0);
}

void	lexer(t_list *lst, char *line)
{
	char	*copy;
	int		i;

	i = 0;
	copy = NULL;
	while (line[i])
	{
		if (lexer_checks(lst, line, &copy, &i) == 1)
			i++;
		else
			copy = joinfree2(copy, line[i++]);
	}
	if (copy)
	{
		addnode(lst, copy);
		free(copy);
		copy = NULL;
	}
	tokenizer(lst);
}
