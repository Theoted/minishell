/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_hd_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:34:39 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/21 11:40:03 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_parent_hd(void)
{
    write(2, "\b\b", 2);
	write(2, "  \n", 3);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	sig_handler_parent_hd(int sig)
{
	(void)sig;
	sig_parent_hd();
}
