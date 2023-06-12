/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:33:20 by rbulanad          #+#    #+#             */
/*   Updated: 2023/06/12 12:57:11 by rbulanad         ###   ########.fr       */
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
	t_list	lst;
	t_list	envlst;
	t_list	sort_envlst;
	char	*line;

	(void)argc;
	(void)argv;
	env_to_lst(&envlst, envp);
	env_to_lst(&sort_envlst, envp);
	while (1)
	{
		lst_init(&lst);
		line = readline(NAME);
		add_history(line);
		if (enter_check(line) != 0)
			continue ;
		if (checker(line) == 1)
			return (freelist(&lst), printf("SYNTAX ERR\n"), 1);
		lexer(&lst, line);
		if (lst.len == 0)
			continue ;
		parser(&lst, envp);
		export_unset(&lst, &envlst, &sort_envlst);
		check_env(&envlst, line);
		freelist(&lst);
		free(line);
	}
	free(line);
	return (0);
}
