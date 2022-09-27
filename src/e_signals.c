/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:07:26 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/27 10:23:01 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int  g_status;

void    sig_handler_parent(int sig)
{
    if (sig == SIGINT)
        g_status =  1;
    sig_parent();
}

void    sig_handler_child(int sig)
{
    signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
}

void    sig_int(int sig)
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

void    sig_quit_exec(int signo)
{
    write(1, "Quit: 3\n", 8);
    g_status = 131;
}

void    sig_int_exec(int signo)
{
    write(2, "\n", 1);
    g_status = 130;
}

void    sig_parent(void)
{
    // write(2, "\n", 1);
    signal(SIGQUIT, sig_quit_exec);
    signal(SIGINT, sig_int_exec);
}

void    sig_child(void)
{
    signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
}
