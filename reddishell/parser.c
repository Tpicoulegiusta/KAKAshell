/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/31 18:11:53 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spe_char(char c)
{
	if (c == 32 || c == '|' || c == '>' || c == '<'
		|| c == '%' || c == '$' || c == '\"' || c == '\'')
		return (1);
	return (0);
}
//utilise 'search' pour trouver la bonne ligne d'env
int	ft_find(char *str, char *search)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!search)
		return (0);
	while (str[i] && search[i] && search[i] == str[i])
		i++;
	if (search[i] == '\0' && str[i] == '=')
		return (1);
	return (0);
}
//cherche et return la bonne ligne d'env ou rien si ne trouve pas
char	*find_envline2(char	*search, char **envp)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = NULL;
	while (envp[i])
	{
		if (ft_find(envp[i], search) == 1)
		{
			while (envp[i][j] != '=')
				j++;
			ret = substr2(envp[i], j + 1, len(envp[i]));
			free(search);
			return (ret);
		}
		i++;
	}
	free(search);
	ret = malloc(sizeof(char) * 1);
	ret[0] = '\0';
	return (ret);
}
//swap le $ par sa var d'env correspondante
/*char	*venv_change(char *str, char **envp)
{
	int		i;
	char	*venv;
	char	*ret;

	i = 0;
	ret = NULL;
	venv = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			while (spe_char(str[i]) == 0 && str[i])
				venv = joinfree2(venv, str[i++]);
			printf("VENV = %s\n", venv);
			venv = find_envline2(venv, envp);
			ret = joinfree(ret, venv);
			free(venv);
			venv = NULL;
		}
		if (str[i])
			ret = joinfree2(ret, str[i++]);
	}
	return (free(str), str = NULL, ret);
}*/
char	*venv_change(char *str, char **envp)
{
	int		i;
	char	*venv;
	char	*ret;

	i = 0;
	ret = NULL;
	venv = NULL;
	if (!str)
		return (NULL);
	if (str[0] == '\"')
		return (str);
	while (str[i])
	{
		if (str[i] == '$' && spe_char(str[i + 1]) == 0)
		{
			i++;
			while (spe_char(str[i]) == 0 && str[i])
				venv = joinfree2(venv, str[i++]);
			printf("VENV = %s\n", venv);
			venv = find_envline2(venv, envp);
			ret = joinfree(ret, venv);
			free(venv);
			venv = NULL;
		}
		if (str[i])
			ret = joinfree2(ret, str[i++]);
	}
	return (free(str), str = NULL, ret);
}

char 	*unquote(char *str, char **envp)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = NULL;
	tmp = NULL;
	while (str[i])  //copie str dans tmp jusqu'a tomber sur une quote
	{
		if (str[i] == '\"')
		{
			i++;
			ret = joinfree(ret, venv_change(tmp, envp)); //a la quote, ajoute le result de venv_change(tmp) a ret
			tmp = NULL;  //reset tmp (tmp est free dans venv_change)
			printf("RET = %s\n", ret);
			while (str[i] != '\"') //copie le contenu des quotes dans le tmp vide
				tmp = joinfree2(tmp, str[i++]);
			if (tmp[0] == '$' && !tmp[1]) //dans le cas ou str contient "$" (tmp = $) on envoie pas le $ dans venv_change, donc joinfree simple
			{
				ret = joinfree(ret, tmp);
				free(tmp);
				tmp = NULL;
			}
			else
			{
				ret = joinfree(ret, venv_change(tmp, envp)); //a la fin des quotes on rajoute une novelle fois le return de venv_change(tmp) a ret
				tmp = NULL;
			}
			printf("RET2 = %s\n", ret);
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				ret = joinfree2(ret, str[i++]);
			i++;
		}
		if (str[i])
			tmp = joinfree2(tmp, str[i++]);
	}
	if (tmp) //si tmp est rempli apres avoir passer les quotes, on le rajoute a ret
	{
		if (len(tmp) == 1) //si il restait qu'1 seul char un joinfree simple
		{
			ret = joinfree(ret, tmp);
			free(tmp);
			tmp = NULL;
		}
		else
			ret = joinfree(ret, venv_change(tmp, envp)); //sinon joinfree + venv_change
	}
	return (free(str), str = NULL, ret);
}
//check si ya un $ et\ou des quotes dans la str
int	venv_check(char *str)
{
	int		i;
	int		dollar;

	i = -1;
	dollar = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			dollar++;
		if ((str[i] == '\"' || str[i] == '\'') && dollar != 0)
			return (1);
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && spe_char(str[i + 1]) == 0)
			return (2);
	}
	return (0);
}

void	parser(t_list *lst, char **envp)
{
	t_node	*tmp;

	tmp = lst->first;
	while (tmp)
	{
		printf("STR BEFORE = %s\n", tmp->str);
		if (venv_check(tmp->str) == 1)
			tmp->str = unquote(tmp->str, envp);
		else if (venv_check(tmp->str) == 2)
			tmp->str = venv_change(tmp->str, envp);
		tmp = tmp->next;
	}
	print_lst(lst);
}
