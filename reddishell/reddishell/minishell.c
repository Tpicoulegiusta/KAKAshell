/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:33:20 by rbulanad          #+#    #+#             */
/*   Updated: 2023/05/11 20:34:05 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

void	freetab(char **tab, int i)
{
	if (tab[i + 1] != NULL)
	{
		i++;
		while (tab[i])
			free(tab[i++]);
		free(tab);
		tab = NULL;
	}
}
/*
void	free_execve(t_data *data)
{
	int	i;

	i = 0;
	free(data->path);
	while (data->argexec[i])
		free(data->argexec[i++]);
	free(data->argexec);
	data->argexec = NULL;
}*/

int	checker(char *line)
{
	if (quote_check(line) != 0 || dobble_pipe(line) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	//t_data data;
	char *line;
	
	while (1)
	{
		line = readline(NAME);
		add_history(line);
		printf("line = %s\n", line);
		if (checker(line) == 0) //a modifie, retour d'erreur avec g_error
		{
			lexer(line);
			//tokenizer(&data);
		}
		/*data.argexec = ft_split(prompt, ' ');
		data.path = getpath(envp, data.argexec[0]);
		if (data.path == NULL)
			ft_printf("%s %s: command not found\n", NAME, prompt);
		else
		{
			exec(&data, envp);
		}*/
	}
	free(line);
	return (0);
}
