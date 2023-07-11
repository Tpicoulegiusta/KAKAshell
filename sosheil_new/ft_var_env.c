/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:19:14 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 18:11:41 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ret = substr2(tmp->str, j + 1, ft_strlen(tmp->str));
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

char	*forquote(char *str, t_list *envlst)
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

void	dollaz(t_list *lst, t_list *envlst)
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
}
