/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportutils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:41:23 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 18:06:37 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**node_tab_setter(t_node *node)
{
	t_node	*tmp;
	char	*join;
	char	**tab;

	tmp = node;
	join = NULL;
	while (node && node->type != piperino)
		node = node->next;
	while (tmp && is_pipe_redir(tmp->str[0]) == 0)
	{
		join = joinfree(join, tmp->str);
		if (tmp->space == 1)
			join = joinfree2(join, ' ');
		tmp = tmp->next;
	}
	tab = ft_split(join, ' ');
	return (free(join), tab);
}

char	*cutter(char *str)
{
	int		i;
	int		start;
	char	*ret;

	i = 0;
	start = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == '=')
			return (substr2(str, start, i));
		i++;
	}
	ret = substr2(str, start, i);
	free(str);
	return (ret);
}

int	check_double(t_list *sort_envlst, char *str)
{
	t_node	*tmp;
	char	*cut1;
	char	*cut2;

	tmp = sort_envlst->first;
	cut1 = NULL;
	cut2 = NULL;
	cut2 = cutter(str);
	while (tmp)
	{
		cut1 = cutter(tmp->str);
		if (ft_strcmp(cut1, cut2) == 0)
		{
			if (ft_find_char(tmp->str, '=') == 0 && ft_find_char(str, '=') == 1)
				return (free(cut1), free(cut2), cut1 = NULL, cut2 = NULL, 1);
			if (ft_find_char(tmp->str, '=') == 1 && ft_find_char(str, '=') == 0)
				return (free(cut1), free(cut2), cut1 = NULL, cut2 = NULL, 2);
			return (free(cut1), free(cut2), cut1 = NULL, cut2 = NULL, 1);
		}
		free(cut1);
		cut1 = NULL;
		tmp = tmp->next;
	}
	return (free(cut1), free(cut2), cut1 = NULL, cut2 = NULL, 0);
}

void	print_export(t_list *lst)
{
	t_node	*tmp;
	int		i;
	int		x;

	tmp = lst->first;
	while (tmp)
	{
		write(1, "declare -x ", 12);
		i = 0;
		x = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == '=' && tmp->str[i + 1] != '\"')
			{
				printf("%c\"", tmp->str[i++]);
				x = 1;
			}
			else
				printf("%c", tmp->str[i++]);
		}
		if (x == 1)
			printf("\"");
		printf("\n");
		tmp = tmp->next;
	}
}

void	del_double(t_list *lst, char *str)
{
	t_node	*tmp;
	char	*cut1;
	char	*cut2;

	cut1 = NULL;
	cut2 = NULL;
	tmp = lst->first;
	cut2 = cutter(str);
	while (tmp)
	{
		cut1 = cutter(tmp->str);
		if (ft_strcmp(cut1, cut2) == 0)
		{
			delnode(lst, tmp);
			break ;
		}
		free(cut1);
		cut1 = NULL;
		tmp = tmp->next;
	}
	free(cut2);
}
