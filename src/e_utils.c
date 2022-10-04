/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:09:20 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/04 14:50:39 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int  g_status;

int execve_error(char *arg)
{
    write(2, arg,
		ft_strlen(arg));
    if (access(arg, F_OK) == -1)
    {
        write(2, ": command not found\n", 21);
        exit(127);
    }
    if (access(arg, X_OK) == -1)
    {
        write(2, ": access denied\n", 17);
        exit(126);
    }
    return (0);
}