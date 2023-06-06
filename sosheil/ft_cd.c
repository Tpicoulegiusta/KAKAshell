/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:36:07 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/05 17:10:31 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_do_cd(t_node *tmp, char **pwd)
{
	if (ft_strcmp(tmp->next->str, ".") == 0)
		return ;
	else if (ft_strcmp(tmp->next->str, "..") == 0)
		return ;
	//else if ()
	return ;
}

void	another_check(t_list *lst, t_node *tmp)
{
	char	*pwd;

	pwd = NULL;
	if (tmp->str[0] == 'c' && tmp->str[1] == 'd')
	{
		if (lst->len > 2)
			if (tmp->next->next->type == piperino)
				return ;
		pwd = getenv("PWD");
		if (tmp->next == NULL)
			pwd = getenv("HOME");
		else if (tmp->next->type == str)
		{
			ft_do_cd(tmp, &pwd);
		}
		printf("pwd -> %s\n\n", pwd);
	}
	//chdir(pwd);
	free(tmp->str);
	tmp->str = pwd;
	printf("tmp->str === %s\n\n", tmp->str);
	return ;
}

// void	parser(t_list *lst, char **envp)
// {
// 	t_node	*tmp;

// 	tmp = lst->first;
// 	printf("str == %s\n", tmp->str);
// 	while (tmp)
// 	{
// 		other_check(tmp);
// 		another_check(tmp);
// 		if (venv_check(tmp->str) == 1)
// 			tmp->str = venv_change(lst, tmp->str, envp);
// 		tmp = tmp->next;
// 	}
// 	print_lst(lst);
// }
