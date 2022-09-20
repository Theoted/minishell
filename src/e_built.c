/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_built.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:09:10 by pat               #+#    #+#             */
/*   Updated: 2022/09/20 09:10:44 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_strcmp(char *arg, char *built)
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

int	ft_exec_built_nofork(t_data_p *d, t_commands *c, int idx)
{
	char	s[1000];

	if (ft_strcmp(c->args_vec[0], "cd"))
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_cd(d, idx));
	}
	if (ft_strcmp(c->args_vec[0], "export"))
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_export(d, idx));
	}
	if (ft_strcmp(c->args_vec[0], "unset"))
	{
		if (d->pipes_nb > 0)
			return (1);
		return (b_unset(d, idx));
	}
	return (0);
}

void	ft_exec_built_fork(t_data_p *d, t_commands *c, int idx)
{
	char	s[1000];

	if (ft_strcmp(c->args_vec[0], "env"))
		print_env_list(d->envp);
	if (ft_strcmp(c->args_vec[0], "pwd"))
	{
		printf("%s\n", getcwd(s, 100));
		exit(0);
	}
	if (ft_strcmp(c->args_vec[0], "echo"))
		b_echo(d, idx);
}
