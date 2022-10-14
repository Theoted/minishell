/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_check_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:58:55 by rmattheo          #+#    #+#             */
/*   Updated: 2022/10/14 18:19:07 by theodeville      ###   ########.fr       */
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
	if (!access(token->args_vec[0], X_OK) && !access(token->args_vec[0], F_OK))
	{
		if (open(token->args_vec[0], O_DIRECTORY) > 0)
		{
			write (2, token->args_vec[0], ft_strlen(token->args_vec[0]));
			write (2, ": Is a directory\n", 18);
			exit (1);
		}
		token->cmd_path = gc_strdup(&data->track, token->args_vec[0]);
		return ;
	}
	data->cmd_slash = gc_strjoin(&data->track, "/", token->args_vec[0]);
	if (data->env_path)
		if (check_path2(data, token) == 0)
			return ;
}
