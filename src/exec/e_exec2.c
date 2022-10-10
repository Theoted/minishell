/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:08:33 by pat               #+#    #+#             */
/*   Updated: 2022/10/10 14:50:57 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_fd_in_pipe(t_tokens *token, int i)
{
	close(token[i].pfd[1]);
	if (token[i].fd_in)
		close(token[i].fd_in);
	if (!token[i + 1].stop)
		token[i + 1].fd_in = dup(token->pfd[0]);
	close(token[i].pfd[0]);
}

void	e_execve(t_data *data, t_tokens *token, int idx)
{
	if (!token->args_vec)
		exit(0);
	if (check_built(token->args_vec[0], token->fd_out))
		ft_exec_built_fork(data, *token, idx);
	else
	{
		if (execve(token->cmd_path, token->args_vec,
				convert_envp(data, data->envp)) == -1)
			execve_error(token->args_vec[0]);
	}
}

void	e_heredoc(t_tokens *token)
{
	int	pipe_heredoc[2];

	pipe(pipe_heredoc);
	write(pipe_heredoc[1], token->here_doc, ft_strlen(token->here_doc));
	close(pipe_heredoc[1]);
	dup2(pipe_heredoc[0], STDIN_FILENO);
	close(pipe_heredoc[0]);
}

/* execution de la commande dans le child */
int	e_child(t_data *data, t_tokens *token, int idx)
{
	if (token->fd_out != 1 && token->fd_out != 0)
	{
		dup2(token->fd_out, STDOUT_FILENO);
		close(token->fd_out);
	}
	if (token->last_in_type == HEREDOC_TYPE)
		e_heredoc(token);
	if (token->last_in_type != HEREDOC_TYPE)
		dup2(token->fd_in, STDIN_FILENO);
	if (token->fd_in)
		close(token->fd_in);
	close(token->pfd[0]);
	if (token->fd_out == 0)
		dup2(token->pfd[1], STDOUT_FILENO);
	close(token->pfd[1]);
	check_path(data, token);
	e_execve(data, token, idx);
	return (1);
}
