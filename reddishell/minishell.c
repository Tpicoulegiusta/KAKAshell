/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:33:20 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/12 12:38:03 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

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
	t_data data;
	t_list lst;
	char *line;

	while (1)
	{
		line = readline(NAME);
		add_history(line);
		if (checker(line) == 1) //a modifie, retour d'erreur avec g_error
			return (1);
		data.lextab = lexer(line);
		tokenizer(&data, &lst);
	}
	free(line);
	return (0);
}
