/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:13:57 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/31 18:48:48 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_list *lst)
{
	t_node	*tmp;

	if (!lst->first)
		return ;
	tmp = lst->first;
	while (tmp)
	{
		if (tmp->str[0] == '|' && !tmp->str[1])
			tmp->type = piperino;
		else if (tmp->str[0] == '>' && !tmp->str[1])
			tmp->type = rr;
		else if (tmp->str[0] == '<' && !tmp->str[1])
			tmp->type = lr;
		tmp = tmp->next;
	}
}

int	lexer_checks(t_list *lst, char *line, char **copy, int *i)
{
	if (quoted(lst, line, copy, i) == 1)
		return (1);
	if (dollar_check(lst, line, copy, i) == 1)
		return (1);
	if (check_32(lst, line[*i], copy) == 1)
		return (1);
	if (check_spe(lst, line[*i], copy) == 1)
		return (1);
	return (0);
}

void	print_lst(t_list *lst)
{
	t_node *tmp;

	tmp = lst->first;
	while (tmp)
	{
		printf("STR = %s ()() TYPE = %d\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
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
		{
			printf("i = %c\n", line[i]);
			i++;
		}
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
