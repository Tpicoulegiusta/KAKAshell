/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:45:42 by sboetti           #+#    #+#             */
/*   Updated: 2023/07/13 19:17:37 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gestion_sig(void)
{
	signal(SIGINT, ft_ctrl_action);
	signal(SIGQUIT, ft_ctrl_action);
}

void	ft_ctrl_action(int signal)
{
	if (signal == 3)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == 2)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	show_ctlr(int b)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (b)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}
