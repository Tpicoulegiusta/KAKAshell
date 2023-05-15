/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:33:02 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/15 14:45:50 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*is_quote(char *line, int *i)
{
	int	start;
	int	end;

	if (line[*i] == 34)
	{
		start = (*i);
		end = *i;
		while (line[*i])
		{
			if (line[*i] == 34)
				end = *i;
			(*i)++;
		}
	}
	*i = end;
	return (substr2(line, start, end + 1));
}*/

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

char	*is_quote(char *line, int *i)
{
	int	start;
	int	end;

	if (line[*i] == 34)
	{
		(*i)++;
		start = (*i);
		end = *i;
		while (line[end] != 34)
			end++;
	}
	*i = end;
	return (substr2(line, start - 1, end + 1));
}

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
		if (line[i] == 34)
		{
			copy = joinfree(copy, is_quote(line, &i));
		}
		else
		{
			if (line[i] == '|')
				copy = joinfree(copy, pipe);
			else
				copy = joinfree2(copy, line[i]);
		}
		i++;
	}
	printf("%s\n", copy);
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
