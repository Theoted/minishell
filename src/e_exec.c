/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/09/27 11:23:42 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
extern int g_status;

int open_infile(t_commands *c, char *infile)
{
    c->fd_in = open(infile, O_DIRECTORY);
    if (c->fd_in != 0 && c->fd_in != -1)
    {
        write(2, infile, ft_strlen(infile));
        write(2, " : is a directory\n", 19);
    }
    close(c->fd_in);
    c->fd_in = open(infile, O_RDONLY);
    if (c->fd_in == -1)
    {
        perror(infile);
        exit(0);
    }
    return (1);
}

/* Ouverture de l'outfile */
int open_outfile(t_commands *c, char *outfile)
{
    c->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0660);
    if (c->fd_out == -1)
    {
        perror(outfile);
        exit(0);
    }
    dup2(c->fd_out, STDOUT_FILENO);
    close(c->fd_out);
    return (1);
}

/* Ouverture de l'outfile_hb */
int open_outfile_hb(t_commands *c, char *outfile_hb)
{
    c->fd_out = open(outfile_hb, O_WRONLY | O_CREAT | O_APPEND, 0660);
    if (c->fd_out == -1)
    {
        perror(outfile_hb);
        exit(0);
    }
    dup2(c->fd_out, STDOUT_FILENO);
    close(c->fd_out);
    return (1);
}

/* Ouverture de tous les files dans l'ordre */
int open_files(t_commands *c)
{
    int i;

    i = -1;
    while (!c->files[++i].stop)
    {
        if (c->files[i].type == INFILE)
        {
            if (open_infile(c, c->files[i].file) == 0)
                return (0);
        }
        else if (c->files[i].type == OUTFILE)
        {
            if (open_outfile(c, c->files[i].file) == 0)
                return (0);
        }
        else if (c->files[i].type == OUTFILE_HB)
        {
            if (open_outfile_hb(c, c->files[i].file) == 0)
                return (0);
        }
    }
    return (1);
}

/* Parcours le tableau de commande et fork 
    apres chaque commandes pour l'executer et creation du pipe */
void    e_exec(t_data_p *d, t_commands *c)
{
    int i;
    int status;

    i = -1;
    // signal(SIGINT, sig_handler_parent);
    while (c[++i].stop == 0)
    {
        if (c[i + 1].stop)
            c[i].fd_out = 1;
        pipe(c[i].pfd);
        if (!ft_exec_built_nofork(d, &c[i], i))
        {
            c[i].pid = fork();
            if (!c[i].pid)
            {
                sig_child();
                signal(SIGINT, sig_handler_child);
                if (e_child(d, &c[i], i) == -1)
                    return ;
            }
            else
                dup_fd_in_pipe(c, i);
        }
        waitpid(c[i].pid, &status, 0);
        if (!WIFSIGNALED(status))
            g_status = WEXITSTATUS(status);
        // else
        //     write(1, "\n", 1);
    }
}