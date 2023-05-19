/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:32:12 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/19 11:42:20 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

void	print_list(t_lst *lst)
{
	t_node	*tmp;

	tmp = lst->first;
	while (tmp)
	{
		printf("node = %s\n", tmp->str);
		tmp = tmp->next;
	}
	printf("len = %d\n", lst->len);
}

int	checker(char *line)
{
	if (quote_check(line) != 0
		|| dobble_pipe(line) != 0 || redir_check(line) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_lst	lst;
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		list_init(&lst);
		line = readline(NAME);
		add_history(line);
		if (enter_check(line) != 0)
			continue ;
		if (checker(line) == 1) //a modifie, retour d'erreur avec g_error
			return (freelst(&lst), printf("SYNTAX ERR"), system("leaks minishell"), 1);
		lexer(&lst, line);
		freelst(&lst);
		free(line);
	}
	free(line);
	return (0);
}
