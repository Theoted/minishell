/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signals2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:07:26 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/29 13:11:20 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	sig_quit_exec(int signo)
{
	write(1, "Quit: 3\n", 8);
	g_status = 131;
}

void	sig_int_exec(int signo)
{
	write(2, "\n", 1);
	g_status = 130;
}

void	sig_parent(void)
{
	signal(SIGQUIT, sig_quit_exec);
	signal(SIGINT, sig_int_exec);
}

void	sig_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
