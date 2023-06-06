/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlc_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:29:46 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/06 17:15:17 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	print_export(t_list *lst)
{
	t_node *tmp;

	tmp = lst->first;
	while (tmp)
	{
		printf("declare -x %s\n", tmp->str);
		tmp = tmp->next;
	}
}

void	sort_lst(t_list *lst1, t_list *lst2)
{
	t_node	*tmp1;
	t_node	*tmp2;

	while (lst2->len != lst1->len)
	{
		tmp1 = lst1->first;
		while (tmp1->space != 0)
			tmp1 = tmp1->next;
		tmp2 = tmp1;
		while (tmp1)
		{	
			if (ft_strcmp(tmp1->str, tmp2->str) < 0 && tmp1->space == 0)
				tmp2 = tmp1;
			tmp1 = tmp1->next;
		}
		tmp2->space = 1;
		addnode(lst2, tmp2->str);
	}
	tmp1 = lst1->first;
	while (tmp1)
	{
		tmp1->space = 0;
		tmp1 = tmp1->next;
	}
}

void	ft_export(char **tab, t_list *envlst)
{
	t_list	sort_envlst;

	if (!tab[1] || tab[1][0] == '|' || tab[1][0] == '<' || tab[1][0] == '>')
	{
		lst_init(&sort_envlst);
		sort_lst(envlst, &sort_envlst);
		print_export(&sort_envlst);
		freelist(&sort_envlst);
	}
	else
	{
		lst_init(&sort_envlst);
		
	}
	freetab(tab);
}

void	export_unset(char *line, t_list *envlst)
{
	char	**tabline;

	tabline = ft_split(line, ' ');
	if (ft_strcmp(tabline[0], "export") == 0)
		ft_export(tabline, envlst);
}
