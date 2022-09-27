/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_hd_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:34:39 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/27 10:57:56 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	sig_parent_hd(void)
{
	write(2, "\b\b", 2);
	write(2, "  \n", 3);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	sig_handler_parent_hd(int sig)
{
	if (sig == SIGINT)
		g_status = 1;
	sig_parent_hd();
}
