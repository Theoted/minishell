/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:25:10 by theodeville       #+#    #+#             */
/*   Updated: 2022/07/15 12:20:27 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    delete_env_node(t_envp **env_lst, char *name)
{
    t_envp  *temp;
    t_envp  *prev;

    temp = *env_lst;
    prev = *env_lst;
    if (temp != NULL && !strncmp_len(temp->name, name))
    {
        *env_lst = temp->next;
        return ;
    }
    while (temp != NULL && strncmp_len(temp->name, name)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
}

void    b_unset(t_data_p *data, int cmd_id)
{
    int i;

    i = 1;
    while (data->commands[cmd_id].args_vec[i])
    {
        delete_env_node(&data->envp, data->commands[cmd_id].args_vec[i]);
        i++;
    }
}