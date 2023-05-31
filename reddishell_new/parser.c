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
char	*venv_change(char *str, char **envp)
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
}

char 	*unquote(char *str)
{
	int		i;
	int		start;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			return (str);
		i++;
	}
		return (free(str), str = NULL, ret);
}

//check si ya un $ et\ou des quotes dans la str
int	venv_check(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
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
		printf("STR FROM LEXER = %s\n", tmp->str);
		if (tmp->type == venv)
		{
			if (venv_check(tmp->str) == 1)
				tmp->str = unquote(tmp->str);
			else if (venv_check(tmp->str) == 2)
				tmp->str = venv_change(tmp->str, envp);
		}
		tmp = tmp->next;
	}
	print_lst(lst);
}
