/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:33:20 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/28 17:44:48 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_lst(t_list *lst)
{
	t_node *tmp;

	tmp = lst->first;
	while (tmp)
	{
		printf("STR = %s\n", tmp->str);
		tmp = tmp->next;
	}
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
	t_data	d;
	char	*line;

	(void)argc;
	(void)argv;
	env_to_lst(&d.envlst, envp);
	env_to_lst(&d.sort_env, envp);
	while (1)
	{
		lst_init(&d.lst);
		line = readline(NAME);
		add_history(line);
		if (enter_check(line) != 0)
			continue ;
		if (checker(line) == 1)
			return (freelist(&d.lst), freelist(&d.envlst), freelist(&d.sort_env), printf("SYNTAX ERR IN MAIN\n"), 1);
		lexer(&d.lst, line);
		if (d.lst.len == 0)
			continue ;
		if (parser(&d.lst, &d.envlst) == 1)
		{
			freelist(&d.lst);
			continue ;
		}
		if (!d.lst.first)
			continue ;
		executor(&d, envp);
		freelist(&d.lst);
		free(line);
	}
	freelist(&d.envlst);
	freelist(&d.sort_env);
	free(line);
	return (0);
}
