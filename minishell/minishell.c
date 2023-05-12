/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:32:12 by sboetti           #+#    #+#             */
/*   Updated: 2023/05/12 14:35:36 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	checker(char *line)
{
	if (enter_check(line) != 0 || quote_check(line) != 0
		|| dobble_pipe(line) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_lst	lst;
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline(NAME);
		add_history(line);
		//a modifie, retour d'erreur avec g_error
		if (checker(line) == 1)
			return (1);
		data.lextab = lexer(line);
		tokenizer(&data, &lst);
	}
	free(line);
	return (0);
}
