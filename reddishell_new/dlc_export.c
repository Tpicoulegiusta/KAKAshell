/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlc_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:29:46 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/08 15:32:12 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/*
char	*add_quotes(char *str)
{
	char	*ret;
	int		i;
	int		x;

	ret = NULL;
	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '\"')
		{
			ret = joinfree2(ret, str[i++]);
			ret = joinfree2(ret, '"');
			x = 1;
		}
		else
			ret = joinfree2(ret, str[i++]);
	}
	if (str[i - 1] != '\"' && x == 1)
		ret = joinfree2(ret, '"');
	return (ret);
}
*/

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
	return (ret);
}

int	ft_find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_tab(t_list *sort_envlst, char *str)
{
	t_node *tmp;
	char	*cut1;
	char	*cut2;

	tmp = sort_envlst->first;
	cut1 = NULL;
	cut2 = NULL;
	cut2 = cutter(str);
	while (tmp)
	{
		cut1 = cutter(tmp->str);
		printf("CUT1= %s, CUT2= %s\n", cut1, cut2);
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
	t_node *tmp;
	int		i;
	int		x;

	tmp = lst->first;
	while (tmp)
	{
		printf("declare -x ");
		i = 0;
		x = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == '=' && tmp->str[i + 1] != '\"')
			{
				printf("%c", tmp->str[i++]);
				printf("\"");
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

void	sort_lst(t_list *lst)
{
	t_list	tmplst;
	t_node	*tmp;
	t_node	*tmp2;
	int		len;

	len = lst->len;
	lst_init(&tmplst);
	while (len != 0)
	{
		if (!lst->first)
			break ;
		tmp = lst->first;
		tmp2 = tmp;
		while (tmp)
		{
			if (ft_strcmp(tmp->str, tmp2->str) < 0)
				tmp2 = tmp;
			tmp = tmp->next;
		}
		addnode(&tmplst, tmp2->str);
		delnode(lst, tmp2);
		len--;
	}
	tmp = tmplst.first;
	while (tmp)
	{
		addnode(lst, tmp->str);
		tmp = tmp->next;
	}
	freelist(&tmplst);
}

void	del_double(t_list *lst, char *str)
{
	t_node *tmp;
	char	*cut1;
	char	*cut2;

	cut1 = NULL;
	cut2 = NULL;
	tmp = lst->first;
	cut2 = cutter(str);
	while(tmp)
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
}

void	ft_export(char **tab, t_list *envlst, t_list *sort_envlst)
{
	(void)envlst;
	if (!tab[1] || tab[1][0] == '|' || tab[1][0] == '<' || tab[1][0] == '>')
	{
		sort_lst(sort_envlst);
		print_export(sort_envlst);
	}
	else
	{
		if (check_tab(sort_envlst, tab[1]) == 1)  // != 0 means que c'est un doublon
		{
			puts("IF");
			del_double(sort_envlst, tab[1]);
			addnode(sort_envlst, tab[1]);
		}
		else if (check_tab(sort_envlst, tab[1]) == 0)
		{
			puts("ELSE IF");
			addnode(sort_envlst, tab[1]);
		}
	}
}

void	export_unset(char *line, t_list *envlst, t_list *sort_envlst)
{
	char	**tabline;

	tabline = ft_split(line, ' ');
	if (ft_strcmp(tabline[0], "export") == 0)
		ft_export(tabline, envlst, sort_envlst);
	freetab(tabline);
}