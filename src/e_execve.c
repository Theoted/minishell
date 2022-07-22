/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:08:33 by pat               #+#    #+#             */
/*   Updated: 2022/07/22 20:18:13 by pat              ###   ########lyon.fr   */
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
		{
			return ;
		}
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
void	e_execve(t_commands *c)
{
	if(ft_strcmp(c->args_vec[0], "cd"))
		exit(0);
	if(ft_strcmp(c->args_vec[0], "env"))
		exit(0);
	if(ft_strcmp(c->args_vec[0], "export"))
		exit(0);
	if(ft_strcmp(c->args_vec[0], "unset"))
		exit(0);
	if(ft_strcmp(c->args_vec[0], "pwd"))
		exit(0);
	if(ft_strcmp(c->args_vec[0], "echo"))
		exit(0);
	if (execve(c->cmd_path, c->args_vec, c->envp) == -1)
	{
		write(2, "bash: ", 6);
		write(2, c->args_vec[0], ft_strlen(c->args_vec[0]));
		write(2, ": command not found\n", 21);
	}
}
