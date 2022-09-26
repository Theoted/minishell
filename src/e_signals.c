/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:07:26 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/26 08:55:55 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	sig_handler_parent(int sig)
{
	if (sig == SIGINT)
		g_status = 1;
	sig_parent();
}

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  ", 2);
		write(2, "\b\b", 2);
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

void	sig_parent(void)
{
	write(2, "\n", 1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	sig_child(void)
{
	g_status = 130;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
