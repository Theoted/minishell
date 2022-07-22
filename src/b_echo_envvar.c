/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:27:36 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/20 14:16:38 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Return 1 si il y a un $ sinon return 0
int check_if_env(char *arg)
{
    int i;

    i = -1;
    while (arg[++i])
        if (arg[i] == '$')
            return (1);
    return (0);
}

// Revoie l'id du prochain dollard si il y en a un sinon va jusqu'a la fin
// de la string
int get_next_dollard_id(char *arg, int i)
{
    while (arg[i])
    {
        if (arg[i] == '$')
            return (i);
        i++;
    }
    return (i);
}

// Recupere une argument dans lequel il y aurais une variable d'environnement
// ou plus et expend ou non les variables presente puis renvoie l'argument
char    *get_echo_env_var(t_data_p *data, char *arg)
{
    int     i;
    int     j;
    char    *new;
    char    *tmp;

    i = -1;
    new = NULL;
    while (arg[++i])
    {
        if (arg[i] != '$')
        {
            if (!new)
                new = gc_substr(&data->track, arg, i, get_next_dollard_id(arg, i));
            else
            {
                new = gc_strjoin(&data->track, new,
                    gc_substr(&data->track, arg, i, get_next_dollard_id(arg, i) - i));
                
            }
            i = get_next_dollard_id(arg, i) - 1;
        }
        else if (arg[i] == '$')
        {
            j = 1;
            while ((ft_isalnum(arg[i + j]) || arg[i + j] == '_') && arg[i + j])
                j++;
            if (j == 1)
                tmp = gc_strdup(&data->track, "$");
            else if (arg[i - 1] && arg[i - 1] == '\'')
                tmp = gc_substr(&data->track, arg, i, j);
            else
            {
                tmp = gc_substr(&data->track, arg, i, j);
                expend_echo_env_vars(data, &tmp); 
            }
            if (!new)
                new = gc_strdup(&data->track, tmp);
            else
                new = gc_strjoin(&data->track, new, tmp);
            i += j - 1;
        }
    }
    return (new);
}

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
