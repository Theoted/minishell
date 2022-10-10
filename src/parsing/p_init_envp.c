/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:05:47 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/10 14:12:28 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_i_init(t_data *data)
{
	char	c[1016];
	char	*s;

	getcwd(c, sizeof(c));
	s = gc_strdup(&data->track, c);
	env_lstadd_back(data, &data->envp, env_lstnew(data, "PWD", s, 1));
	env_lstadd_back(data, &data->envp, env_lstnew(data, "SHLVL", "0", 1));
	env_lstadd_back(data, &data->envp,
		env_lstnew(data, "_", "/usr/bin/env", 1));
}
