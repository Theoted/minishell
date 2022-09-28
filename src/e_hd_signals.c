/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_hd_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:34:39 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/27 13:31:43 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	sig_parent_hd(void)
{
	write(2, "\n", 1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	sig_handler_parent_hd(int sig)
{
	if (sig == SIGINT)
		g_status = 1;
	sig_parent_hd();
}
