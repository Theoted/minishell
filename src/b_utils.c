/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:25:46 by theodeville       #+#    #+#             */
/*   Updated: 2022/07/15 12:10:39 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Cette fonction permet d'executer un strncmp avec
// comme longueur la string la plus grande
int strncmp_len(char *s1, char *s2)
{
    int len;
    
    if (ft_strlen(s1) < ft_strlen(s2))
        len = ft_strlen(s2);
    else
        len = ft_strlen(s1);
    return (ft_strncmp(s1, s2, len));
}

void print_env_list(t_envp *env_list)
{
  while (env_list)
  {
	printf("%s=%s\n", env_list->name, env_list->content);
	env_list = env_list->next;
  }
}
