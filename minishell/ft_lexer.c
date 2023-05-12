/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:33:02 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/12 16:08:06 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lexer(char *line)
{
	char	**tab;
	char	*copy;
	char	*pipe;
	int		i;

	i = 0;
	copy = NULL;
	pipe = NULL;
	pipe = joinfree(pipe, " | ");
	while (line[i])
	{
		if (line[i] == '|')
			copy = joinfree(copy, pipe);
		else
			copy = joinfree2(copy, line[i]);
		i++;
	}
	tab = ft_minisplit(copy, ' ');
	return (tab);
}

void	tokenizer(t_data *data, t_lst *lst)
{
	t_tok	*tmp;

	if (lst->first)
		freelst(lst);
	lst = create_list(data->lextab, lst);
	tmp = lst->first;
	while (tmp)
	{
		printf("tok = %s\n", tmp->tok);
		tmp = tmp->next;
	}
}
