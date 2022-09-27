/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:21:05 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/27 10:29:05 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int     g_status;

int check_spaces(char *arg)
{
    int i;

    i = -1;
    while (arg[++i])
    {
        if (arg[i] != ' ')
            return (1);
    }
    return (0);
}

void    free_all(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        free(arg[i]);
        i++;
    }
    free(arg);
}

int main(int ac, char **av, char **envp)
{
    t_data_p            data_p;

    (void)ac;
    (void)av;
    data_p.track = NULL;
    data_p.env_vars = envp;
    init_our_envp(&data_p);
    find_env_path(data_p.envp, &data_p);
    while (1)
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, sig_int);
        data_p.stdin_arg = readline("\033[0;34mShellDePetiteTaille-0.0.42: \033[0m");
        sig_parent();
        add_history(data_p.stdin_arg);
        if (!data_p.stdin_arg)
        {
            printf("exit\n");
            gc_free_all(&data_p.track);
            return (0);
        }
        if (!check_spaces(data_p.stdin_arg))
        {
            free(data_p.stdin_arg);
            continue ;
        }
        if (data_p.stdin_arg[0])
        {
            if (!lexer(data_p.stdin_arg, &data_p))
                e_exec(&data_p, data_p.commands);

        }
        if (data_p.stdin_arg)
            free(data_p.stdin_arg);
    }
    gc_free_all(&data_p.track);
    free(data_p.stdin_arg);
    return (0);
}
