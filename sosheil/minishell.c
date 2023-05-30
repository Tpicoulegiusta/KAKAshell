/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:32:12 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/29 10:10:18 by sboetti          ###   ########.fr       */
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
	if (quote_check(line) != 0)
		return (1);
	if (dobble_pipe(line) != 0 || redir_check(line) != 0
			|| semi(line) != 0 || backslash(line) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_lst	lst;
	char	*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline(NAME);
		printf("Debut de boucle\n");
		add_history(line);
		if (enter_check(line) != 0)
			continue ;
		list_init(&lst);
		if (checker(line) == 1)
			return (freelst(&lst), printf("SYNTAX ERR\n"), 1);
		lexer(&lst, line);
		parser(&lst, envp);
		freelst(&lst);
		free(line);
		printf("Tour de boucle\n");
	}
	printf("avant bug\n");
	free(line);
	printf("apres bug\n");
	return (0);
}

