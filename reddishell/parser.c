/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/26 20:04:01 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// $ + certains char speciaux va quand meme chercher (!, @, #, $, *, &)
// pour tout autres char speciaux ca devrait skip la substitution de $,
// (ex: "$'HOME'" --> $'HOME', "$<HOME" --> $<HOME ... )

int	spe_char(char c)
{
	if (c == 32 || c == '|' || c == '>' || c == '<'
		|| c == '\"' || c == '\'' || c == '%')
		return (1);
	return (0);
}
//check si ya un $ dans la str
int	venv_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != 32)
			return (1);
		i++;
	}
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
char	*venv_change(t_list *lst, char *str, char **envp)
{
	int		i;
	char	*venv;
	char	*ret;

	i = 0;
	ret = NULL;
	venv = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (spe_char(str[i]) == 0 && str[i])
				venv = joinfree2(venv, str[i++]);
			printf("QUOTED? = %d\n", lst->node.quote);
			printf("VENV = %s\n", venv);
			if (!venv && lst->node.quote == 1)
			{
				puts("QUOTED");
				return (str);
			}
			venv = find_envline2(venv, envp);
			ret = joinfree(ret, venv);
		}
		if (lst->node.quote == 0 && quoted(str, &ret, &i) == 1)
			i++;
		if (str[i])
			ret = joinfree2(ret, str[i++]);
	}
	return (ret);
}

void	parser(t_list *lst, char **envp)
{
	t_node	*tmp;

	tmp = lst->first;
	while (tmp)
	{
		if (venv_check(tmp->str) == 1)
			tmp->str = venv_change(lst, tmp->str, envp);
		tmp = tmp->next;
	}
	print_lst(lst);
}
