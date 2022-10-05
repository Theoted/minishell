/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_check_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:58:55 by rmattheo          #+#    #+#             */
/*   Updated: 2022/10/05 20:20:27 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_path2(t_data_p *d, t_commands *c)
{
	int	i;

	i = -1;
	while (d->env_path[++i])
	{
		c->cmd_path = gc_strjoin(&d->track,
				d->env_path[i], d->cmd_slash);
		if (!access(c->args_vec[0], X_OK))
		{
			c->cmd_path = c->args_vec[0];
			return (0);
		}
		if (!access(c->cmd_path, X_OK))
			return (0);
		gc_free_malloc(&d->track, (void **)&c->cmd_path);
	}
	return (1);
}

void	check_path(t_data_p *d, t_commands *c)
{
	if (!c->args_vec)
		return ;
	if (!ft_strncmp(c->args_vec[0], "./", 2))
	{
		c->cmd_path = gc_strdup(&d->track, c->args_vec[0]);
		return ;
	}
	d->cmd_slash = gc_strjoin(&d->track, "/", c->args_vec[0]);
	if (d->env_path)
		if (check_path2(d, c) == 0)
			return ;
}
