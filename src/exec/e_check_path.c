/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_check_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:58:55 by rmattheo          #+#    #+#             */
/*   Updated: 2022/10/07 01:11:23 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_path2(t_data *data, t_tokens *token)
{
	int	i;

	i = -1;
	while (data->env_path[++i])
	{
		token->cmd_path = gc_strjoin(&data->track,
				data->env_path[i], data->cmd_slash);
		if (!access(token->args_vec[0], X_OK))
		{
			token->cmd_path = token->args_vec[0];
			return (0);
		}
		if (!access(token->cmd_path, X_OK))
			return (0);
		gc_free_malloc(&data->track, (void **)&token->cmd_path);
	}
	return (1);
}

void	check_path(t_data *data, t_tokens *token)
{
	if (!token->args_vec)
		return ;
	if (!ft_strncmp(token->args_vec[0], "./", 2))
	{
		token->cmd_path = gc_strdup(&data->track, token->args_vec[0]);
		return ;
	}
	data->cmd_slash = gc_strjoin(&data->track, "/", token->args_vec[0]);
	if (data->env_path)
		if (check_path2(data, token) == 0)
			return ;
}
