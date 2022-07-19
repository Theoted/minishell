/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:27:36 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/19 15:26:56 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int expend_echo_env_vars(t_data_p *data, char **arg)
{
    char *tmp;

    tmp = *arg;
    if (*arg[0] == '$')
    {
        *arg = expend_env_var(data, data->envp, *(arg) + 1);
        if (!strncmp_len(gc_strjoin(&data->track, "$", *arg), tmp))
            *arg = gc_strdup(&data->track, "");
    }
    return (0);
}