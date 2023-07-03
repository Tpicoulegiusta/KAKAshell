/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:37:15 by tpicoule          #+#    #+#             */
/*   Updated: 2023/07/03 17:00:55 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

t_node	*find_node(char *key, t_list *env)
{
	t_node	*tmp;

	tmp = env->first;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->str, ft_strlen(key)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	other_check(t_node *tmp, t_list *env)
{
	char	*s;
	t_node	*node;

	s = getcwd(NULL, 0);
	if (tmp->next)
	{
		printf("c'est quoi ces arguments de GOLMON la\n");
		return (1); //return 1
	}
	if (s)
		printf("%s\n", s);
	else
	{
		node = find_node("PWD", env);
		if (node)
			printf("%s\n", node->str);
		return (1) ; //return 1
	}
	if (tmp->str)
		free(tmp->str);
	tmp->str = ft_strdup(s);
	free(s);
	return (0) ; //return 0
}
