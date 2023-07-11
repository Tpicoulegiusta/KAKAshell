/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:32:12 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/11 18:31:50 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_lst(t_list *lst)
// {
// 	t_node	*tmp;

// 	tmp = lst->first;
// 	while (tmp)
// 	{
// 		printf("STR = %s; TYPE = %d; SPACE = %d\n",
// 			tmp->str, tmp->type, tmp->space);
// 		tmp = tmp->next;
// 	}
//}

int	checker(char *line)
{
	if (quote_check(line) != 0)
		return (1);
	if (dobble_pipe(line) != 0 || redir_check(line) != 0
		|| semi(line) != 0 || backslash(line) != 0)
		return (1);
	return (0);
}

t_node	*find_node(char *key, t_list *env)
{
	t_node	*tmp;

	tmp = NULL;
	if (env->first != NULL)
		tmp = env->first;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->str, ft_strlen(key)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_mainutils(char *line, t_data *d)
{
	add_history(line);
	if (enter_check(line) != 0)
		return (1);
	if (checker(line) == 1)
		return (freelist(&(d->lst)), freelist(&(d->envlst)), \
		freelist(&(d->sort_env)), printf("SYNTAX ERR IN MAIN\n"), 1);
	lexer(&(d->lst), line);
	if (d->lst.len == 0)
		return (1);
	if (parser(&(d->lst), &(d->envlst)) == 1)
	{
		freelist(&(d->lst));
		free(line);
		return (1);
	}
	if (!d->lst.first)
		return (1);
	executor(d);
	freelist(&(d->lst));
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	d;
	char	*line;

	(void)argv;
	if (argc > 1)
		return (0);
	ft_env_to_list(&d.envlst, envp);
	ft_env_to_list(&d.sort_env, envp);
	gestion_sig();
	while (1)
	{
		list_init(&d.lst);
		show_ctlr(0);
		line = readline(NAME);
		show_ctlr(1);
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		if (ft_mainutils(line, &d) == 1)
			continue ;
	}
	return (0);
}
