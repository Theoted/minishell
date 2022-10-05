/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_built.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:09:10 by pat               #+#    #+#             */
/*   Updated: 2022/10/05 20:42:46 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	strcmp_ncs(char *arg, char *built)
{
	int	i;

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

int	ft_exec_built_nofork2(t_data_p *d, t_commands *c, int idx)
{
	if (!c->args_vec)
		return (0);
	if (strcmp_ncs(c->args_vec[0], "unset"))
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_unset(d, idx));
	}
	if (strcmp_ncs(c->args_vec[0], "exit"))
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_exit(d, idx));
	}
	return (0);
}

int	ft_exec_built_nofork(t_data_p *d, t_commands *c, int idx)
{
	if (!c->args_vec)
		return (0);
	if (strcmp_ncs(c->args_vec[0], "cd"))
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_cd(d, idx));
	}
	if (strcmp_ncs(c->args_vec[0], "export") && c->args_vec[1])
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_export(d, idx));
	}
	return (ft_exec_built_nofork2(d, &c[idx], idx));
}

void	ft_exec_built_fork(t_data_p *d, t_commands *c, int idx)
{
	char	s[1000];

	if (strcmp_ncs(c->args_vec[0], "env"))
		print_env_list(d->envp);
	if (strcmp_ncs(c->args_vec[0], "pwd"))
	{
		printf("%s\n", getcwd(s, 100));
		exit(0);
	}
	if (strcmp_ncs(c->args_vec[0], "echo"))
		b_echo(d, idx);
	if (strcmp_ncs(c->args_vec[0], "export") && ((!c->args_vec[1])
			|| ((c->args_vec[1]) && c->fd_out)))
		b_export(d, idx);
}
