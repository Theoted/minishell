/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:25:46 by theodeville       #+#    #+#             */
/*   Updated: 2022/10/10 11:38:09 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Cette fonction permet d'executer un strncmp avec
// comme longueur la string la plus grande
// Renvoie 0 si les strings sont les memes
int	strncmp_len(char *s1, char *s2)
{
	int	len;

	if (!s1 || !s2)
		return (-1);
	if (ft_strlen(s1) < ft_strlen(s2))
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1);
	return (ft_strncmp(s1, s2, len));
}

void	print_env_list(t_envp *env_list)
{
	t_envp	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->name && tmp->equal == 1)
		{
			if (tmp->content)
				printf("%s=%s\n", tmp->name, tmp->content);
			else if (!tmp->content)
				printf("%s=\n", tmp->name);
		}
		tmp = tmp->next;
	}
	exit(0);
}
