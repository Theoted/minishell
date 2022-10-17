/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:21:05 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 17:30:32 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	check_spaces(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] != ' ')
			return (1);
	}
	return (0);
}

void	ft_core_parsing_exec(t_data *data)
{
	if (data->stdin_arg[0])
	{
		if (!lexer(data->stdin_arg, data))
		{
			change_termios(RESET);
			e_exec(data, data->commands);
		}
	}
}

static int	ft_while_main(t_data *data)
{
	while (1)
	{
		signo();
		data->stdin_arg
			= readline("\033[0;34mShellDePetiteTaille-0.0.42: \033[0m");
		if (ft_ctrl_d(data))
			return (0);
		sig_parent();
		if (check_spaces(data->stdin_arg))
			add_history(data->stdin_arg);
		if (!check_spaces(data->stdin_arg))
		{
			change_termios(RESET);
			free(data->stdin_arg);
			continue;
		}
		ft_core_parsing_exec(data);
		change_termios(RESET);
		if (data->stdin_arg)
			free(data->stdin_arg);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	data.track = NULL;
	data.env_vars = envp;
	init_our_envp(&data);
	find_env_path(data.envp, &data);
	if (!ft_while_main(&data))
		return (0);
	gc_free_all(&data.track);
	free(data.stdin_arg);
	return (0);
}
