/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:50:02 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/10 13:49:06 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int new_2d_len(char **new)
// {
//     int i;

//     i = -1;
//     while (new[++i])
//         ;
//     return (i);
// }

// char    **new_args_vec(t_data *data, char **new, int idx, int i)
// {
//     char    **new_args;
//     int     av_len;
//     int     j;
//     int     k;

//     j = -1;
//     av_len = double_arr_len(data->commands[idx].args_vec);
//     new_args = gc_calloc(av_len + double_arr_len(new) + 1,
//         sizeof(char *), &data->track);
//     while (++j < av_len + double_arr_len(new))
//     {
//         if (j == i)
//         {
//             while (new[j])
//             {
//                 new_args[j] == gc_strdup(&data->track, new[j]);
//                 j++;
//             }
//         }
//     }
// }

// int check_spaces2(char *arg)
// {
//     int i;

//     i = -1;
//     while (arg[++i])
//     {
//         if (arg[i] == ' ')
//             return (1);
//     }
//     return (0);
// }

// int parse_space(t_data *data, char **args, int idx)
// {
//     // int     i;
//     // char    **new;

//     // i = -1;
//     // new = NULL;
//     // while (args[++i])
//     // {
//     //     if (check_spaces2(args[i])
            
//     // }
//     return (0);
// }