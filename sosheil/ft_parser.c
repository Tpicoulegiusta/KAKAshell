/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:33:04 by sboetti           #+#    #+#             */
/*   Updated: 2023/06/08 12:09:47 by tpicoule         ###   ########.fr       */
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
			ret = substr2(envp[i], j + 1, ft_strlen(envp[i]));
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
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '\"')
		{
			i++;
			while (spe_char(str[i]) == 0 && str[i])
				venv = joinfree2(venv, str[i++]);
		//	printf("VENV = %s\n", venv);
			venv = find_envline2(venv, envp);
			ret = joinfree(ret, venv);
			free(venv);
			venv = NULL;
		}
		else if (str[i])
			ret = joinfree2(ret, str[i++]);
	}
	return (free(str), str = NULL, ret);
}

char 	*forquote(char *str, char **envp)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (str[i] == '\'')
		return (str);
	ret = joinfree(ret, venv_change(str, envp));
	return (ret);
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

void	fake_exec(t_list *lst)
{
	t_node	*tmp;
	char	*str;

	tmp = lst->first;
	str = NULL;
	while (tmp)
	{
		free(tmp->str);
		tmp->str = ft_strdup(unquote(tmp->str));
		str = joinfree(str, tmp->str);
		tmp = tmp->next;
	}
	printf("AFTER STR = %s\n\n", str);
	free(str);
}

void	parser(t_list *lst, t_list *envlst, char **envp)
{
	t_node	*tmp;
	t_node	*tmp2;

	tmp = lst->first;
	another_check(lst, envlst, tmp);
	while (tmp)
	{
		printf("STR FROM LEXER = %s ()() TYPE = %d\n", tmp->str, tmp->type);
		other_check(tmp, envlst);
		if (tmp != lst->last && tmp->str[0] == '$' && !tmp->str[1])
		{
			tmp2 = tmp;
			tmp = tmp->next;
			delnode(lst, tmp2);
		}
		if (tmp && tmp->type == venv)
		{
			if (venv_check(tmp->str) == 1)
				tmp->str = forquote(tmp->str, envp);
			else
				tmp->str = venv_change(tmp->str, envp);
		}
		if (tmp)
			tmp = tmp->next;
	}
	print_lst(lst);
	//fake_exec(lst);
}
