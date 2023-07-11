/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:33:20 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/11 19:52:47 by rbulanad         ###   ########.fr       */
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
	t_node	*tmp;

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

void	envlst_envtab(t_data *d)
{
	char	*tmp;
	t_node	*node;

	tmp = NULL;
	node = d->envlst.first;
	if (d->envtab)
		freetab(d->envtab);
	while (node)
	{
		tmp = joinfree(tmp, node->str);
		tmp = joinfree2(tmp, ' ');
		node = node->next;
	}
	d->envtab = ft_split(tmp, ' ');
	free(tmp);
}

t_node	*find_node(char *key, t_list *env)
{
	t_node	*tmp;

	tmp = NULL;
	if (env->first != NULL)
		tmp = env->first;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->str, len(key)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
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
		d.envtab = NULL;
		lst_init(&d.lst);
		line = readline(NAME);
		if (!line) //////// for CTRL-D
		{
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		if (enter_check(line) != 0)
			continue ;
		if (checker(line) == 1)
			return (freelist(&d.lst), freelist(&d.envlst), \
				freelist(&d.sort_env), printf("SYNTAX ERR IN MAIN\n"), 1);
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
		envlst_envtab(&d);
		executor(&d);
		freetab(d.envtab);
		freelist(&d.lst);
		free(line);
	}
	return (0);
}
