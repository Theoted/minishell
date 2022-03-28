/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:52:41 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/22 10:08:35 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int state_checker(char *str, int start, int len)
{
    int i;
    int	quote;

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
