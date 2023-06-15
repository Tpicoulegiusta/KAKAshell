/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/15 10:34:01 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spe_char(char c)
{
	if ((c >= 32 && c <= 47) || c == '\'' || c == '\"' || c == '=')
		return (1);
	return (0);
}

//utilise 'search' pour trouver la bonne ligne d'env
int	ft_find(char *str, char *search)
{
	int	i;

	i = 0;
	if (!search)
		return (0);
	while (str[i] && search[i] && search[i] == str[i])
		i++;
	if (search[i] == '\0' && str[i] == '=')
		return (1);
	return (0);
}
//cherche et return la bonne ligne d'env ou rien si ne trouve pas
char	*find_envline2(char	*search, t_list *envlst)
{
	int		j;
	char	*ret;
	t_node	*tmp;

	j = 0;
	ret = NULL;
	tmp = envlst->first;
	while (tmp)
	{
		if (ft_find(tmp->str, search) == 1)
		{
			while (tmp->str[j] != '=')
				j++;
			ret = substr2(tmp->str, j + 1, len(tmp->str));
			free(search);
			return (ret);
		}
		tmp = tmp->next;
	}
	free(search);
	ret = malloc(sizeof(char) * 1);
	ret[0] = '\0';
	return (ret);
}

//swap le $ par sa var d'env correspondante
char	*venv_change(char *str, t_list *envlst)
{
	int		i;
	char	*venv;
	char	*ret;

	i = 0;
	ret = NULL;
	venv = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '\"')
		{
			i++;
			while (spe_char(str[i]) == 0 && str[i])
				venv = joinfree2(venv, str[i++]);
			//printf("VENV = %s\n", venv);
			venv = find_envline2(venv, envlst);
			ret = joinfree(ret, venv);
			free(venv);
			venv = NULL;
		}
		else if (str[i])
			ret = joinfree2(ret, str[i++]);
	}
	return (free(str), str = NULL, ret);
}

char 	*forquote(char *str, t_list *envlst)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (str[i] == '\'')
		return (str);
	ret = joinfree(ret, venv_change(str, envlst));
	return (ret);
}

//check si ya des quotes dans la str
int	venv_check(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
	}
	return (0);
}

char	*unquote(char *str)
{
	char	*ret;
	int		i;

	i = 1;
	ret = NULL;
	if (str[0] == '\"')
	{
		while (str[i] != '\"')
			ret = joinfree2(ret, str[i++]);
		return (free(str), str = NULL, ret);
	}
	if (str[0] == '\'')
	{
		while (str[i] != '\'')
			ret = joinfree2(ret, str[i++]);
		return (free(str), str = NULL, ret);
	}
	return (str);
}

char	**prep_exec(t_list *lst)
{
	t_node	*tmp;
	char	*str;
	char	**tab;
	int		i;

	i = 0;
	tmp = lst->first;
	str = NULL;
	while (tmp)
	{
		printf("node[%d] = %s ()() TYPE = %d\n", i, tmp->str, tmp->type);
		tmp->str = unquote(tmp->str);
		str = joinfree(str, tmp->str);
		if (tmp->space == 1)
			str = joinfree2(str, ' ');
		tmp = tmp->next;
		i++;
	}
	tab = ft_split(str, ' ');
	return (free(str), str = NULL, tab);
}

//no need de gerer $$, $1, $2, $3, $#, $! etc...
char	**parser(t_list *lst, t_list *envlst)
{
	t_node	*tmp;
	t_node	*tmp2;

	tmp = lst->first;
	while (tmp)
	{
		if (tmp != lst->last && tmp->str[0] == '$' && !tmp->str[1])
		{
			tmp2 = tmp;
			tmp = tmp->next;
			delnode(lst, tmp2);
		}
		if (tmp && tmp->type == venv)
		{
			if (venv_check(tmp->str) == 1)
				tmp->str = forquote(tmp->str, envlst);
			else
				tmp->str = venv_change(tmp->str, envlst);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (prep_exec(lst));
}
