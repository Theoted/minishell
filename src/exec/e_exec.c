/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/10/17 17:26:05 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_waitpid(t_tokens *token, int i)
{
	int	status;

	waitpid(token[i].pid, &status, 0);
	return (status);
}

void	waitpid_close(t_data *data, t_tokens *token)
{
	int	i;
	int	status;

	i = -1;
	while (!token[++i].stop)
	{
		if (token[i].pfd[0])
			close(token[i].pfd[0]);
		if (token[i].pfd[1])
			close(token[i].pfd[1]);
	}
	i = -1;
	while (token[++i].pid)
		status = ft_waitpid(token, i);
	if (!WIFSIGNALED(status))
		g_status = WEXITSTATUS(status);
	else if (g_status == 131)
		write(1, "Quit: 3\n", 8);
	else if (g_status == 130)
		write(1, "\n", 1);
	check_fork_error(data, token);
}

int	ft_fork(t_data *data, t_tokens *token, int i)
{
	if (!token->args_vec)
	{
		return (1);
	}
	token[i].pid = fork();
	if (token[i].pid == -1)
	{
		if (data->fork_error == 0)
			write(2, "fork: Resource temporarily unavailable\n", 40);
		data->fork_error = 1;
		g_status = 1;
		close(token[i].pfd[0]);
		close(token[i].pfd[1]);
		return (1);
	}
	else if (!token[i].pid)
	{
		sig_child();
		if (e_child(data, &token[i], i) == -1)
			return (0);
	}
	else
		dup_fd_in_pipe(token, i);
	return (1);
}

void	e_exec(t_data *data, t_tokens *token)
{
	int	i;

	i = -1;
	while (token[++i].stop == 0)
	{
		if (token[i + 1].stop)
			token[i].fd_out = 1;
		pipe(token[i].pfd);
		if (open_files(&token[i]))
		{
			if (!ft_exec_built_nofork(data, token[i], i))
			{
				if (!ft_fork(data, token, i))
					return ;
			}
		}
		else
			dup_fd_in_pipe(token, i);
		if (token[i].fd_out != 1 && token[i].fd_out != 0)
			close(token[i].fd_out);
	}
	waitpid_close(data, token);
}
