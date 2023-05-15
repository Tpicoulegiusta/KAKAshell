/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:13:57 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/12 12:38:34 by rbulanad         ###   ########.fr       */
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
	tab = ft_split(copy, ' ');
	return (tab);
}

void	tokenizer(t_data *data, t_list *lst)
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