/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:34:18 by tpicoule          #+#    #+#             */
/*   Updated: 2023/06/16 14:10:07 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_daeja(t_list *envlst)
// {
// 	if (envlst->pwd->str != NULL)
// 		free(envlst->pwd->str);
// 	envlst->pwd->str = ft_ministrchr(envlst->pwd->str, '=');
// 	return ;
// }

// int	check_pwd(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] == ' ')
// 		i++;
// 	if (str[i] == 'p' && str[i + 1] == 'w' && str[i + 2] == 'd'
// 		&& (str[i + 3] == ' ' || str[i + 3] == '\0'))
// 		return (0);
// 	return (1);
// }

// void	init_pwd(t_list *envlst)
// {
// 	t_node	*env;

// 	env = envlst->first;
// 	envlst->pwd = malloc(sizeof(t_node));
// 	while (env)
// 	{
// 		if (ft_strncmp(env->str, "PWD", 3) == 0)
// 			envlst->pwd->str = ft_strdup(env->str);
// 		env = env->next;
// 	}
// 	ft_daeja(envlst);
// 	return ;
// }

// void	other_check(t_node *tmp, t_list *envlst)
// {
// 	if (tmp->prev == NULL)
// 	{
// 		if (check_pwd(tmp->str) == 0)
// 		{
// 			if (envlst->pwd == NULL)
// 				init_pwd(envlst);
// 			free(tmp->str);
// 			tmp->str = ft_strdup(envlst->pwd->str);
// 		}
// 	}
// 	else if (tmp->prev->type == piperino && check_pwd(tmp->str) == 0)
// 	{
// 		if (envlst->pwd == NULL)
// 			init_pwd(envlst);
// 		free(tmp->str);
// 		tmp->str = ft_strdup(envlst->pwd->str);
// 	}
// 	return ;
// }

void	other_check(t_node *tmp, t_list *env)
{
	char	*s;
	t_node	*node;

	s = getcwd(NULL, 0);
	if (tmp->next)
	{
		printf("c'est quoi ces arguments de GOLMON la\n");
		return ; //return 1
	}
	if (s)
		printf("%s\n", s);
	else
	{
		node = find_node("PWD", env);
		if (node)
			printf("%s\n", node->str);
		return ; //return 1
	}
	if (tmp->str)
		free(tmp->str);
	tmp->str = ft_strdup(s);
	free(s);
	return ; //return 0
}
