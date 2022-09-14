/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:21:05 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/12 15:01:03 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

void	free_all(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void	rm_chapeau_c(void)
{
	struct termios t;
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	sig_handler(int signo)
{
	if (signo == 2)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main(int ac, char **av, char **envp)
{
	t_data_p			data_p;
	struct sigaction	sa;

	rm_chapeau_c();
	sa.sa_handler = &sig_handler;
	sigaction(2, &sa, NULL);
	(void)ac;
	(void)av;
	data_p.track = NULL;
	data_p.env_vars = envp;
	init_our_envp(&data_p);
	find_env_path(data_p.envp, &data_p);
	while (1)
	{
		data_p.stdin_arg = readline("\033[0;34mShellDePetiteTaille-0.0.42: \033[0m");
		add_history(data_p.stdin_arg);
		if (b_exit(data_p.stdin_arg))
			break ;
		if (data_p.stdin_arg == NULL)
			break ;
		if (!check_spaces(data_p.stdin_arg))
			continue ;
		if (data_p.stdin_arg[0])
		{
			if (!lexer(data_p.stdin_arg, &data_p))
				e_exec(&data_p, data_p.commands);
		}
		if (data_p.stdin_arg)
			free(data_p.stdin_arg);
	}
	gc_free_all(&data_p.track);
	free(data_p.stdin_arg);
	return (0);
}
