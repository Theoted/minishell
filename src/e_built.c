/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_built.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:09:10 by pat               #+#    #+#             */
/*   Updated: 2022/10/05 09:11:50 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int	strcmp_ncs(char *arg, char *built)
// {
// 	int	i;

// 	i = -1;
// 	if (ft_strlen(arg) != ft_strlen(built))
// 		return (0);
// 	while (arg[++i])
// 	{
// 		if (arg[i] != built[i])
// 			return (0);
// 	}
// 	return (1);
// }

int	ft_exec_built_nofork2(t_data_p *d, t_commands *c, int idx)
{
	char	s[1000];

	if (!c->args_vec)
		return (0);
	if (!strncmp_ncs(c->args_vec[0], "unset"))
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_unset(d, idx));
	}
	if (!strncmp_ncs(c->args_vec[0], "exit"))
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_exit(d, idx));
	}
	return (0);
}

int	ft_exec_built_nofork(t_data_p *d, t_commands *c, int idx)
{
	char	s[1000];
	// dprintf(2, "check builtins no fork-> parent\n");
	if (!c->args_vec)
		return (0);
	if (!strncmp_ncs(c->args_vec[0], "cd"))
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_cd(d, idx));
	}
	if (!strncmp_ncs(c->args_vec[0], "export") && !c->fd_out)
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_export(d, idx));
	}
	ft_exec_built_nofork2(d, &c[idx], idx);
	// dprintf(2, "Pas de builtins à no fork-> parent\n");
	return (0);
}

void	ft_exec_built_fork(t_data_p *d, t_commands *c, int idx)
{
	char	s[1000];

	if (!strncmp_ncs(c->args_vec[0], "env"))
		print_env_list(d->envp);
	if (!strncmp_ncs(c->args_vec[0], "pwd"))
	{
		printf("%s\n", getcwd(s, 100));
		exit(0);
	}
	if (!strncmp_ncs(c->args_vec[0], "echo"))
		b_echo(d, idx);
	if (!strncmp_ncs(c->args_vec[0], "export") && c->fd_out)
		b_export(d, idx);
}
