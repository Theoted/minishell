/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:10:09 by pat               #+#    #+#             */
/*   Updated: 2022/07/05 14:28:22 by pat              ###   ########lyon.fr   */
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
	t_data_p d;
	int i = 0;
	d.pipes_nb = 1;
	d.commands = calloc(sizeof(t_commands), 2);
	d.commands[0].files = calloc(sizeof(t_files), 4);
	d.commands[0].files[0].file = "infile";
	d.commands[0].files[0].type = INFILE;
	dprintf(2, "d.commands[0].files[0].file = %s\n", d.commands[0].files[0].file);
	d.commands[0].files[1].file = "outfile";
	d.commands[0].files[1].type = OUTFILE;
	dprintf(2, "d.commands[0].files[0].outfile = %s\n", d.commands[0].files[1].file);
	d.commands[0].files[2].file = "outfile_hb";
	d.commands[0].files[2].type = OUTFILE_HB;
	dprintf(2, "d.commands[0].files[0].outfile_hb = %s\n", d.commands[0].files[2].file);
	d.commands[0].files[3].stop = 1;
	
	d.commands[0].last_in_type = INFILE_TYPE;
	d.commands[0].here_doc = 0;
	d.commands[0].cmd_path = "/bin/cat";
	d.commands[0].args_vec = ft_split(argv[1], ' ');
	d.commands[0].envp = envp;
	d.commands[0].stop = 0;


	// d.commands[1].here_doc = 0;
	// d.commands[1].cmd_path = "/usr/bin/head";
	// d.commands[1].args_vec = ft_split(argv[2], ' ');
	// d.commands[1].envp = envp;
	// d.commands[1].stop = 0;

	d.commands[1].stop = 1;
	e_exec(d.commands);
	return (0);
}