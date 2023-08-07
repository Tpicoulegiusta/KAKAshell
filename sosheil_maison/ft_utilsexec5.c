/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilsexec5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:05:30 by sboetti           #+#    #+#             */
/*   Updated: 2023/08/07 00:05:30 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_pipe_utils(t_data *d)
{
	close(d->fd[0]);
	dup2(d->fd[1], STDOUT_FILENO);
	close(d->fd[1]);
}

void	enter_the_heredoc(t_data *d, char *limit, int i)
{
	char	*line;

	line = NULL;
	d->stock_hd = NULL;
	d->fd_hd[i] = malloc(sizeof(int) * 2);
	pipe(d->fd_hd[i]);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, limit) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, d->fd_hd[i][1]);
		ft_putchar_fd('\n', d->fd_hd[i][1]);
	}
	close(d->fd_hd[i][1]);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!str)
		i = 0;
	else
	{
		i = 0;
		while (str[i])
		{
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
}

void	ex_body_utils(t_data *d, t_node *node)
{
	check_env(&d->envlst, node);
	export_unset(node, &d->envlst, &d->sort_env);
	ft_cd(d, node);
	ft_built_exit(node);
}
