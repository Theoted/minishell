/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signals2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:07:26 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/07 01:34:38 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_ctrl_d(t_data *data)
{
	if (!data->stdin_arg)
	{
		change_termios(RESET);
		printf("exit\n");
		gc_free_all(&data->track);
		return (1);
	}
	return (0);
}

void	sig_quit_exec(int sig)
{
	(void)sig;
	g_status = 131;
}

void	sig_int_exec(int sig)
{
	(void)sig;
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
