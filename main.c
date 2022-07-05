/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:21:05 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/05 17:37:49 by pat              ###   ########lyon.fr   */
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
	data_p.commands[0].last_in_type = INFILE_TYPE;
	data_p.commands[0].here_doc = 0;
	data_p.commands[0].cmd_path = "/bin/cat";
	
	data_p.commands[0].args_vec = ft_split("catt", ' ');
	data_p.commands[0].envp = envp;
	data_p.commands[0].stop = 0;
	e_exec(&data_p, data_p.commands);
	gc_free_all(&data_p.track);
	free(data_p.stdin_arg);
	return (0);
}
