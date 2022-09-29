/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:42:35 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/29 11:49:18 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ncs = no case sensitive
int strncmp_ncs(char *s1, char *s2)
{
	int	len;
    int i;

	if (!s1 || !s2)
		return (-1);
	if (ft_strlen(s1) < ft_strlen(s2))
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1);
    while (len > i && s1[i] && 
        (s1[i] == s2[i] || s1[i] == s2[i] + 32 || s1[i] == s2[i] - 32))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
