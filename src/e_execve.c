/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:08:33 by pat               #+#    #+#             */
/*   Updated: 2022/07/25 15:53:20 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_path(t_data_p *d, t_commands *c)
{
	int	i;

	i = -1;
	/* Permet de validé une commande qui est donné directement par sont chemin d'acces */
	if (access(c->args_vec[0], X_OK) && c->args_vec[0])
		c->cmd_path = gc_strdup(&d->track, c->args_vec[0]);
	d->cmd_slash = gc_strjoin(&d->track, "/", c->args_vec[0]);
	/* Check les commandes dans les variables d'environnement */
	while (d->env_path[++i])
	{
		c->cmd_path = gc_strjoin(&d->track,
			d->env_path[i], d->cmd_slash);
		if (!access(c->args_vec[0], X_OK))
		{
			c->cmd_path = c->args_vec[0];
			return ;
		}
		if (!access(c->cmd_path, X_OK))
			return ;
		gc_free_malloc(&d->track, (void **)&c->cmd_path);
	}
}
static int ft_strcmp(char *arg, char *built)
{
	int i;

	i = -1;
	if (ft_strlen(arg) != ft_strlen(built))
		return (0);
	while (arg[++i])
	{
		if (arg[i] != built[i])
			return (0);
	}
	return (1);
}
int	ft_exec_built_nofork(t_data_p *d, t_commands *c, int idx)
{
	char    s[1000];

	if(ft_strcmp(c->args_vec[0], "cd"))
		 return(b_cd(d, idx));
	if(ft_strcmp(c->args_vec[0], "export"))
		return(b_export(d, idx));
	if(ft_strcmp(c->args_vec[0], "unset"))
		return(b_unset(d, idx));
	return (0);
}
void	ft_exec_built_fork(t_data_p *d, t_commands *c, int idx)
{
	char	s[1000];

	if(ft_strcmp(c->args_vec[0], "env"))
		print_env_list(d->envp);
	if(ft_strcmp(c->args_vec[0], "pwd"))
	{
		printf("%s\n", getcwd(s, 100));
		exit(0);
	}
	if(ft_strcmp(c->args_vec[0], "echo"))
		b_echo(d, idx);
}

void	e_execve(t_data_p *d,t_commands *c, int idx)
{
	ft_exec_built_fork(d, c, idx);
	if (execve(c->cmd_path, c->args_vec, c->envp) == -1)
	{
		write(2, "bash: ", 6);
		write(2, c->args_vec[0], ft_strlen(c->args_vec[0]));
		write(2, ": command not found\n", 21);
	}
}
