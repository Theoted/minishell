/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:07:26 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/10 14:18:34 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	change_termios(int action)
{
	static struct termios	old_termios;
	struct termios			new_termios;

	if (action == SET)
	{
		tcgetattr(0, &old_termios);
		new_termios = old_termios;
		new_termios.c_lflag &= ~ECHOCTL;
		tcsetattr(0, 0, &new_termios);
	}
	else
	{
		tcsetattr(0, 0, &old_termios);
	}
}

void	sig_handler_parent(int sig)
{
	if (sig == SIGINT)
		g_status = 1;
	sig_parent();
}

void	sig_handler_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}
