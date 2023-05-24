/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:33:20 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/24 16:32:05 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

void	print_list(t_list *lst)
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
	t_list	lst;
	char	*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		list_init(&lst);
		line = readline(NAME);
		add_history(line);
		if (enter_check(line) != 0)
			continue ;
		if (checker(line) == 1)
			return (freelist(&lst), printf("SYNTAX ERR\n"), 1);
		lexer(&lst, line);
		parser(&lst, envp);
		freelist(&lst);
		free(line);
	}
	free(line);
	return (0);
}
