/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exec_built_ins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:09:41 by theodeville       #+#    #+#             */
/*   Updated: 2022/07/18 10:24:00 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    exec_built_ins(t_data_p *data, int idx, char *builtin)
{
    char    s[1000];
    
    if (!strncmp_len(builtin, "echo"))
        b_echo(data, idx);
    else if (!strncmp_len(builtin, "cd"))
        b_cd(data, idx);
    else if (!strncmp_len(builtin, "pwd"))
        printf("%s\n", getcwd(s, 100));
    else if (!strncmp_len(builtin, "export"))
        b_export(data, idx);
    else if (!strncmp_len(builtin, "unset"))
        b_unset(data, idx);
    else if (!strncmp_len(builtin, "env"))
        print_env_list(data->envp);
}