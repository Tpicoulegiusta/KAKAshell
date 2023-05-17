/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:33:20 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/17 13:23:08 by rbulanad         ###   ########.fr       */
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
	if (enter_check(line) != 0 || quote_check(line) != 0 || dobble_pipe(line) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_list lst;
	char *line;

	while (1)
	{
		list_init(&lst);
		line = readline(NAME);
		add_history(line);
		if (checker(line) == 1) //a modifie, retour d'erreur avec g_error
			return (1);
		lexer(&lst, line);
		print_list(&lst);
		freelist(&lst);
	}
	free(line);
	return (0);
}
