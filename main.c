/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:21:05 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/05 15:20:20 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

void	sig_handler(int signo)
{
	printf("coucou\n");
	(void)signo;
}

int main(int ac, char **av, char **envp)
{
	t_data_p		data_p;
	
	signal(SIGINT, sig_handler);
	// sleep(10);
	(void)ac;
	(void)av;
	data_p.track = NULL;
	find_env_path(envp, &data_p);
	data_p.env_vars = envp;
	while (1)
	{
		data_p.stdin_arg = readline("\033[0;34mShellDePetiteTaille-0.0.42: \033[0m");
		if (data_p.stdin_arg[0])
			lexer(data_p.stdin_arg, &data_p);
		break ;
	}
	gc_free_all(&data_p.track);
	free(data_p.stdin_arg);
	return (0);
}
