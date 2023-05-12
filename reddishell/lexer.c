/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:13:57 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/12 10:43:41 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char *line)
{
	int	i;
	int	single;
	int	dobble;

	i = 0;
	single = 0;
	dobble = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			single++;
		if (line[i] == '\"')
			dobble++;
		i++;
	}
	if (single % 2 != 0 || dobble % 2 != 0)
		return (1);
	return (0);
}

int	dobble_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	lexer(char *line)
{
	//char	**tab;
	char	*copy;
	char	*pipe;
	int		i;

	i = 0;
	copy = NULL;
	pipe = NULL;
	pipe = joinfree(pipe, " | ", 0);
	while (line[i])
	{
		if (line[i] == '|')
			copy = joinfree(copy, pipe, 0);
		else
			copy = joinfree(copy, NULL, line[i]);
		i++;
	}
	/*tab = ft_split(copy, ' ');
	return (tab);*/
}

void	tokenizer(t_data *data)
{
	t_list	*list;
	t_tok	*tmp;

	list = NULL;
	list = create_list(data->lextab, list);
	tmp = list->first;
	while (tmp->next)
	{
		printf("tok = %s\n", tmp->tok);
		tmp = tmp->next;
	}
}
