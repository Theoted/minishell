/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:31:14 by theodeville       #+#    #+#             */
/*   Updated: 2022/07/15 11:32:42 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int b_exit(char *input)
{
    if (!strncmp_len("exit", input))
    {
        write(1, "exit\n", 5);
        return (1);
    }
    return (0);
}