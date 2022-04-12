/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:10:09 by pat               #+#    #+#             */
/*   Updated: 2022/04/12 13:43:51 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	sig_handler(int signo)
{
	printf("coucou\n");
	(void)signo;
}

int main (int argc, char **argv, char **envp)
{
	signal(SIGINT, sig_handler);
	int infile = open("infile", O_RDONLY);
	int outfile = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0660);
	t_data_p d;
	int i = 0;
	d.pipes_nb = 1;
	d.commands = calloc(sizeof(t_commands), 3);
	d.commands[0].infile = infile;
	d.commands[0].outfile = 0;
	d.commands[0].here_doc = "Bonjour je m'appelle steel\n";
	d.commands[0].infile_type = 0;
	d.commands[0].cmd_path = "/bin/cat";
	d.commands[0].args_vec = ft_split(argv[1], ' ');
	d.commands[0].envp = envp;
	d.commands[0].stop = 0;

	d.commands[1].infile = 0;
	d.commands[1].outfile = 0;
	d.commands[1].here_doc = 0;
	d.commands[1].infile_type = 0;
	d.commands[1].cmd_path = "/usr/bin/head";
	d.commands[1].args_vec = ft_split(argv[2], ' ');
	d.commands[1].envp = envp;
	d.commands[1].stop = 0;

	// d.commands[2].infile = 0;
	// d.commands[2].outfile = outfile;
	// d.commands[2].here_doc = 0;
	// d.commands[2].infile_type = 0;
	// d.commands[2].cmd_path = "/bin/cat";
	// d.commands[2].args_vec = ft_split(argv[3], ' ');
	// d.commands[2].envp = envp;
	// d.commands[2].stop = 0;

	// d.commands[3].infile = 0;
	// d.commands[3].outfile = outfile;
	// d.commands[3].here_doc = 0;
	// d.commands[3].infile_type = 0;
	// d.commands[3].cmd_path = "/bin/ls";
	// d.commands[3].args_vec = ft_split(argv[4], ' ');
	// d.commands[3].envp = envp;
	// d.commands[3].stop = 0;
	
	// d.commands[4].infile = 0;
	// d.commands[4].outfile = outfile;
	// d.commands[4].here_doc = 0;
	// d.commands[4].infile_type = 0;
	// d.commands[4].cmd_path = "/usr/bin/head";
	// d.commands[4].args_vec = ft_split(argv[2], ' ');
	// d.commands[4].envp = envp;
	// d.commands[4].stop = 0;
	// d.commands[2].infile = 0;
	// d.commands[2].outfile = outfile;
	// d.commands[2].here_doc = 0;
	// d.commands[2].infile_type = 0;
	// d.commands[2].cmd_path = "/bin/cat";
	// d.commands[2].args_vec = ft_split(argv[3], ' ');
	// d.commands[2].envp = envp;

	d.commands[2].stop = 1;
	e_exec(&d, d.commands);
	
	return (0);
}