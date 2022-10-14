/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_built.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:09:10 by pat               #+#    #+#             */
/*   Updated: 2022/10/14 15:32:45 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_built_nofork2(t_data *data, t_tokens token, int idx)
{
	if (!token.args_vec)
		return (0);
	if (!strncmp_ncs(token.args_vec[0], "unset"))
	{
		if (data->pipes_nb > 0)
			return (1);
		return (b_unset(data, idx));
	}
	if (!strncmp_ncs(token.args_vec[0], "exit"))
	{
		if (data->pipes_nb > 0)
			return (1);
		return (b_exit(data, idx));
	}
	return (0);
}

int	ft_exec_built_nofork(t_data *data, t_tokens token, int idx)
{
	if (!token.args_vec)
		return (0);
	if (!strncmp_ncs(token.args_vec[0], "cd"))
	{
		if (data->pipes_nb > 0)
			return (1);
		return (b_cd(data, idx));
	}
	if (!strncmp_ncs(token.args_vec[0], "export"))
	{
		int err;
		if (data->pipes_nb > 0)
			return (0);
		err = b_export(data, idx);
		if(err)
			return (1);
		if(err == -1)
		{
	
			write(2, "export :", 9);
			write(2, data->commands[idx].args_vec[1], strlen(data->commands[idx].args_vec[1]));
			write(2, ": not a valid identifier\n", 26);
			g_status = 1;
			exit(0);
		}
	}
	return (ft_exec_built_nofork2(data, token, idx));
}

void	ft_exec_built_fork(t_data *data, t_tokens token, int idx)
{
	char	s[1000];
	char	*err;

	err = NULL;
	if (!strncmp_ncs(token.args_vec[0], "env"))
		print_env_list(data, data->envp, idx);
	if (!strncmp_ncs(token.args_vec[0], "pwd"))
	{
		if (!(*s))
		{
			err = find_node_content("PWD", data->envp);
			dprintf(2, "%s\n", err);
		}
		else
			dprintf(2, "%s\n", getcwd(s, 100));
		exit(0);
	}
	if (!strncmp_ncs(token.args_vec[0], "echo"))
		b_echo(data, idx);
	if (!strncmp_ncs(token.args_vec[0], "export"))
	{
		if(b_export(data, idx) == -1)
		{
			write(2, "export :", 9);
			write(2, data->commands[idx].args_vec[1], strlen(data->commands[idx].args_vec[1]));
			write(2, ": not a valid identifier\n", 26);
			g_status = 1;
			exit(0);
		}
	}
}
