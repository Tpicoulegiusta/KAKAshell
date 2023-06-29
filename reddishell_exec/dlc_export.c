/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlc_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:29:46 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/29 10:43:34 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
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
//le chercheur de doublons
int	check_double(t_list *sort_envlst, char *str)
{
	t_node *tmp;
	char	*cut1;
	char	*cut2;

	tmp = sort_envlst->first;
	cut1 = NULL;
	cut2 = NULL;
	cut2 = cutter(str); //on cut jusquau '=', '=' exclus
	while (tmp)
	{
		cut1 = cutter(tmp->str);
		if (ft_strcmp(cut1, cut2) == 0)
		{
			if (ft_find_char(tmp->str, '=') == 0 && ft_find_char(str, '=') == 1) //doublon + doit etre replaced + add dans env
				return (free(cut1), free(cut2), cut1 = NULL, cut2 = NULL, 1);
			if (ft_find_char(tmp->str, '=') == 1 && ft_find_char(str, '=') == 0) //doublon mais ne doit pas etre replaced
				return (free(cut1), free(cut2), cut1 = NULL, cut2 = NULL, 2);
			return (free(cut1), free(cut2), cut1 = NULL, cut2 = NULL, 1); //doublon + doit etre replaced
		}
		free(cut1);
		cut1 = NULL;
		tmp = tmp->next;
	}
	return (free(cut1), free(cut2), cut1 = NULL, cut2 = NULL, 0); //pas de doublons
}
//print l'export char par char en ajoutant les quotes apres le '=' et "declare -x" au debut
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
//tri la liste, pushswap style
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

void	del_double(t_list *lst, char *str) //sera replaced par unset
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
	if (check_double(sort_envlst, str) == 1)  // means que c'est un doublon + add dans env
	{
		del_double(sort_envlst, str);
		addnode(sort_envlst, str);
		export_env(envlst, str);
	}
	else if (check_double(sort_envlst, str) == 0) //pas de doublons
	{
		export_env(envlst, str);
		addnode(sort_envlst, str);
	}
	//else il ya un doublon mais ne doit pas etre replaced, donc ne fait rien
}

int	spe_char_exp_uns(char c)
{
	if ((c >= 37 && c <= 59)
		|| c == '=' || c == '!' || c == '?'
		|| c == '\"' || c == '#')
		return (1);
	return (0);
}

int	is_pipe_redir(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

char	**node_tab_setter(t_node *node)
{
	t_node	*tmp;
	char	*join;

	tmp = node;
	join = NULL;
	while (node)
	{
		if (is_pipe_redir(node->str[0]) == 1)
			break;
		node = node->next;
	}
	while (tmp && is_pipe_redir(tmp->str[0]) == 0)
	{
		join = joinfree(join, tmp->str);
		if (tmp->space == 1)
			join = joinfree2(join, ' ');
		tmp = tmp->next;
	}
	char **tab = ft_split(join, ' ');
	return (free(join), tab );
}

//l'export dans toute sa grandeur
void	ft_export(t_node *node, t_list *envlst, t_list *sort_envlst)
{
	char	**tmptab;
	int		i;
	
	if (!node->next)
	{
		sort_lst(sort_envlst);
		print_export(sort_envlst);
	}
	else
	{
		tmptab= node_tab_setter(node);

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
	}
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

void	export_unset(t_node *node, t_list *envlst, t_list *sort_envlst)
{
	if (ft_strcmp(node->str, "export") == 0)
		ft_export(node, envlst, sort_envlst);
	if (ft_strcmp(node->str, "unset") == 0)
		ft_unset(node, envlst, sort_envlst);
}
