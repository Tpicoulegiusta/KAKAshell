/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:19:29 by rbulanad          #+#    #+#             */
/*   Updated: 2023/07/12 17:42:54 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_checks(int builtin, t_node *node)
{
	if (builtin)
	{
		if (!ft_strcmp("cd", node->str))
			return (1);
		if (!ft_strcmp("exit", node->str))
			return (1);
		if (ft_strcmp(node->str, "export") == 0 && node->next
			&& node->next->type != piperino)
			return (1);
		if (ft_strcmp(node->str, "unset") == 0)
			return (1);
	}
	return (0);
}

int	exec_builtin_checks_pipe(int builtin, t_node *node)
{
	if (builtin)
	{
		if (!ft_strcmp("cd", node->str))
			return (1);
		if (!ft_strcmp("exit", node->str))
			return (1);
		if (ft_strcmp(node->str, "unset") == 0)
			return (1);
	}
	return (0);
}

void	child_func(t_data *d, t_node *node)
{
	if (d->builtin)
	{
		if (d->argpath)
			free(d->argpath);
		freetab(d->tabexec);
		if (!ft_strcmp("echo", node->str))
			ft_echo(node);
		if (!ft_strcmp("pwd", node->str))
			ft_pwd(node, &(d->envlst));
		check_env(&d->envlst, node);
		export_unset(node, &d->envlst, &d->sort_env);
		exit(0);
	}
	else
	{
		execve(d->argpath, d->tabexec, d->envtab);
		if (!d->argpath && !d->builtin)
		{
			fprintf(stderr, "command not found\n");
			exit(0);
		}
	}
}

void	child_func_pipes(t_data *d, t_node *node)
{
	if (d->builtin)
	{
		if (d->argpath)
			free(d->argpath);
		freetab(d->tabexec);
		check_env(&d->envlst, node);
		if (!ft_strcmp("echo", node->str))
			ft_echo(node);
		if (!ft_strcmp("pwd", node->str))
			ft_pwd(node, &(d->envlst));
		if (ft_strcmp(node->str, "export") == 0 && node->next
			&& node->next->type != piperino)
			exit (1);
		export_unset(node, &d->envlst, &d->sort_env);
		exit(0);
	}
	else
	{
		execve(d->argpath, d->tabexec, d->envtab);
		if (!d->argpath || !d->builtin)
		{
			fprintf(stderr, "command not found\n");
			exit(0);
		}
	}
}

t_node	*executor_body(t_data *d, t_node *node)
{
	d->scan_pipe = 0;
	node = scan_out_infiles(d, node);
	if (d->scan_pipe == 1)
	{
		if (execute_pipes(d, node) == 1)
		{
			check_env(&d->envlst, node);
			export_unset(node, &d->envlst, &d->sort_env);
			ft_cd(d, node);
			ft_built_exit(node);
		}
	}
	else
	{
		if (execute(d, node) == 1)
		{
			check_env(&d->envlst, node);
			export_unset(node, &d->envlst, &d->sort_env);
			ft_cd(d, node);
			ft_built_exit(node);
		}
	}
	close_fds(d);
	return (node);
}
