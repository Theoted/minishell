/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:56:07 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/20 14:14:30 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Cette fonction retourne l'id de la prochaine quote identique
// A utiliser lorsqu'on rencontre une quote alors que nous ne somme dans
// Aucune quote
int next_quote_id(char *arg, char quote, int i)
{
    i++;
    while (arg[i])
    {
        if (arg[i] == quote)
            return (i);
        i++;
    }
    return (-1);
}

// Cette fonction retourne l'id de la fin du mot ou jusqu'a la prochaine
// quote sachant que nous ne somme pas dans une quote
int word_end_id(char *arg, int i)
{
    while (arg[i])
    {
        if (arg[i] == '\'' || arg[i] == '\"')
            return (i);
        i++;
    }
    return (i);
}

// Cette fonction supprimer les quotes a supprimer dans l'argument
void parse_quotes(t_data_p *data, t_echo *echo_data)
{
    char *tmp;

    tmp = NULL;
    if (echo_data->new == NULL)
        echo_data->new = gc_substr(&data->track, echo_data->arg, echo_data->idx + 1,
                                   next_quote_id(echo_data->arg, echo_data->quote, echo_data->idx) - 1);
    else
    {
        tmp = echo_data->new;
        echo_data->new = gc_substr(&data->track, echo_data->arg, echo_data->idx + 1,
                                   next_quote_id(echo_data->arg, echo_data->quote, echo_data->idx) - 1 - echo_data->idx);
        echo_data->new = gc_strjoin(&data->track, tmp, echo_data->new);
    }
}

// Cette fonction recuperer les mots qui ne sont pas entre quotes
void e_create_arg(t_data_p *data, t_echo *echo_data)
{
    char *tmp;

    tmp = NULL;
    if (echo_data->new == NULL)
        echo_data->new = gc_substr(&data->track, echo_data->arg, echo_data->idx,
                                   word_end_id(echo_data->arg, echo_data->idx));
    else
    {
        tmp = echo_data->new;
        echo_data->new = gc_substr(&data->track, echo_data->arg, echo_data->idx,
                                   word_end_id(echo_data->arg, echo_data->idx) - echo_data->idx);
        echo_data->new = gc_strjoin(&data->track, tmp, echo_data->new);
    }
}

// Cette fonction est la fonction PRINCIPALE qui permet de parser l'argument de
// echo en lui enlevant les quotes necessaires
char *remove_quotes(t_data_p *data, char *arg)
{
    t_echo echo_data;
    int i;

    i = -1;
    echo_data.new = "";
    echo_data.quote = 0;
    echo_data.arg = arg;
    while (arg[++i])
    {
        echo_data.idx = i;
        if ((arg[i] == '\'' || arg[i] == '\"') && !state_checker(arg, 0, i))
        {
            echo_data.quote = arg[i];
            if (next_quote_id(arg, echo_data.quote, i) != -1)
            {
                parse_quotes(data, &echo_data);
                i = next_quote_id(arg, echo_data.quote, i);
                echo_data.quote = 0;
            }
        }
        else if ((arg[i] != '\'' || arg[i] != '\"') && !state_checker(arg, 0, i))
        {
            e_create_arg(data, &echo_data);
            i = word_end_id(arg, i) - 1;
        }
    }
    return (echo_data.new);
}

// Retourne 1 si le premier char de l'argument a un tiret et un 'n' 
// ou plus sinon retourne 0
int check_n(char *arg)
{
    int i;

    i = 1;
    if (arg[0] != '-')
        return (0);
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int arg_vec_len(t_data_p *data, int idx)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (data->commands[idx].args_vec[++i])
        j++;
    return (j);
}

int b_echo(t_data_p *data, int idx)
{
    int i;
    int bn;
    char *new;
    int av_len;
    int check;

    i = 0;
    bn = 1;
    new = NULL;
    av_len = arg_vec_len(data, idx);
    check = 0;
    while (data->commands[idx].args_vec[++i])
    {
        if (check_n(data->commands[idx].args_vec[i]) && check == 0)
        {
            bn = 0;
            continue ;
        }
        check = 1;
        data->commands[idx].args_vec[i] = get_echo_env_var
            (data, data->commands[idx].args_vec[i]);
        printf("%s", remove_quotes(data, data->commands[idx].args_vec[i]));
        if (av_len > 2 && i < av_len)
            printf(" ");
    }
    if (bn)
        printf("\n");
    return (0);
}