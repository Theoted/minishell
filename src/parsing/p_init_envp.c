/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:05:47 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 17:25:12 by tdeville         ###   ########lyon.fr   */
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

int	quote_check_return(char quote)
{
	if (quote)
	{
		g_status = 258;
		printf("Quotes: Synthax error\n");
		return (1);
	}
	return (0);
}

void	check_fork_error(t_data *data, t_tokens *token)
{
	if (data->fork_error == 1)
	{
		g_status = 1;
		close(token[0].pfd[0]);
		close(token[0].pfd[1]);
	}
}
