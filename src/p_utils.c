/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:52:41 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/05 15:41:24 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Cette fonction permet de savoir si on est dans des guillemets
int state_checker(char *str, int start, int len)
{
    int i;
    int quote;

    i = start;
    quote = 0;
    while (str[i] && i < len)
    {
        if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
            quote = str[i];
        else if (str[i] == quote && quote != 0)
            quote = 0;
        i++;
    }
    return (quote);
}

// Cette fonction permet de savoir le dernier infile dans l'ordre
// < ou <<
int last_in_redir(char *arg)
{
    int check;
    int i;

    check = 0;
    i = -1;
    while (arg[++i])
    {
        if (arg[i] == '<')
        {
            if (arg[i + 1] == '<')
            {
                check = 2;
                i++;
            }
            else
                check = 1;
        }
    }
    return (check);
}

/*
Cette fonction est celle qui va remplire le tabl de structure t_files
qui se trouve dans chaque t_commands
*/
int get_in_out_files(char *arg, t_data_p *data, int idx)
{
    int i;
    int j;
    int len;
    int in_type;

    i = -1;
    j = -1;
    len = 0;
    in_type = 0;
    data->commands[idx].files = gc_calloc(count_in_out_files(arg) + 1,
                                          sizeof(t_files), &data->track);
    data->commands[idx].files[count_in_out_files(arg) + 1].stop = 1;
    while (arg[++i])
    {
        if (arg[i] == '<' || arg[i] == '>')
        {
            len = get_file(arg, &i, &in_type);
            if (len != -1)
            {
                data->commands[idx].files[++j].file = gc_substr(&data->track, arg, i, len);
                data->commands[idx].files[j].type = in_type;
            }
        }
    }
    return (0);
}

/*
Cette fonction permet de recuperer le type de file (type),
de mettre l'index dans l'argument au debut du nom du file
et de recuperer l'index de la fin du mot pour pouvoir le
substr
*/
int get_file(char *arg, int *start, int *type)
{
    int i;

    i = 0;
    if (arg[(*start)] == '<')
        if (arg[(*start) + 1] == '<')
            return (idx_after_hd(arg, start));
    (*type) = 1;
    if (arg[(*start)] == '>')
    {
        if (arg[(*start) + 1] == '>')
        {
            (*type) = 3;
            (*start)++;
        }
        else
            (*type) = 2;
    }
    (*start)++;
    while (arg[(*start)] == ' ' && arg[(*start)])
        (*start)++;
    while ((arg[(*start) + i] != ' ' && arg[(*start) + i] != '<' 
            && arg[(*start) + i] != '>') && arg[(*start) + i])
        i++;
    return (i);
}

// Cette fonction permet de set l'id apres un here_doc
// pour pouvoir continuer a recuperer les <, >, >>
int idx_after_hd(char *arg, int *start)
{
    int i;

    i = 0;
    (*start)++;
    while (arg[(*start)] == ' ' && arg[(*start)])
        (*start)++;
    while ((arg[(*start) + i] != ' ' && arg[(*start) + i] != '<' 
            && arg[(*start) + i] != '>') && arg[(*start) + i])
        i++;
    return (-1);
}

// cette fonction compte le nombre de <, >, >>
int count_in_out_files(char *arg)
{
    int i;
    int count;

    i = -1;
    count = 0;
    while (arg[++i])
    {
        if (arg[i] == '<')
        {
            if (arg[i + 1] == '<')
                i++;
            else
                count++;
        }
        else if (arg[i] == '>')
        {
            if (arg[i + 1] == '>')
                i++;
            count++;
        }
    }
    return (count);
}
