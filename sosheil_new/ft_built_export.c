/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:00:08 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 17:07:05 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//print l'export char par char en ajoutant les quotes apres le '=' et "declare -x" au debut
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

void	del_double(t_list *lst, char *str) //sera replaced par unset
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

//pour rajouter dans l'env
void	export_env(t_list *envlst, char	*str)
{
	if (ft_find_char(str, '=') == 1)
	{
		if (check_double(envlst, str) == 1)
		{
			del_double(envlst, str);
			addnode(envlst, str);
		}
		else if (check_double(envlst, str) == 0)
			addnode(envlst, str);
	}
}

void	if_else_double(t_list *sort_envlst, t_list *envlst, char *str)
{
	if (check_double(sort_envlst, str) == 1)
	{
		del_double(sort_envlst, str);
		addnode(sort_envlst, str);
		export_env(envlst, str);
	}
	else if (check_double(sort_envlst, str) == 0)
	{
		export_env(envlst, str);
		addnode(sort_envlst, str);
	}
}


//l'export dans toute sa grandeur
int	ft_export(t_node *node, t_list *envlst, t_list *sort_envlst)
{
	char	**tmptab;
	int		i;

	if (!node->next || (node->next && node->next->type == piperino))
	{
		sort_lst(sort_envlst);
		print_export(sort_envlst);
		return (0);
	}
	tmptab = node_tab_setter(node);
	i = 1;
	while (tmptab[i])
	{
		if (spe_char_exp_uns(tmptab[i][0]) == 1)
		{
			printf("EXPORT SYNTAX ERR\n");
			i++;
		}
		if (tmptab[i])
			if_else_double(sort_envlst, envlst, tmptab[i++]);
	}
	free(tmptab);
	return (1);
}

void	search_and_del(t_list *envlst, t_list *sort_envlst, char *str)
{
	t_node	*tmp;
	char	*cutstr;

	tmp = envlst->first;
	while (tmp)
	{
		cutstr = NULL;
		cutstr = cutter(tmp->str);
		if (ft_strcmp(cutstr, str) == 0)
			delnode(envlst, tmp);
		tmp = tmp->next;
		free(cutstr);
	}
	tmp = sort_envlst->first;
	while (tmp)
	{
		cutstr = NULL;
		cutstr = cutter(tmp->str);
		if (ft_strcmp(cutstr, str) == 0)
		delnode(sort_envlst, tmp);
		tmp = tmp->next;
		free(cutstr);
	}
}

void	ft_unset(t_node *node, t_list *envlst, t_list *sort_envlst)
{
	if (!node->next)
		return ;
	node = node->next;
	while (node && is_pipe_redir(node->str[0]) == 0)
	{
		if (spe_char_exp_uns(node->str[0]) == 1)
		{
			printf("UNSET SYNTAX ERR\n");
			node = node->next;
			continue ;
		}
		if (!node)
			break ;
		search_and_del(envlst, sort_envlst, node->str);
		node = node->next;
	}
}

int	export_unset(t_node *node, t_list *envlst, t_list *sort_envlst)
{
	int	export;

	if (ft_strcmp(node->str, "export") == 0)
	{
		export = ft_export(node, envlst, sort_envlst);
		return (export);
	}
	if (ft_strcmp(node->str, "unset") == 0)
	{
		ft_unset(node, envlst, sort_envlst);
		return (1);
	}
	return (0);
}
