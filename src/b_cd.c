/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:51:37 by theodeville       #+#    #+#             */
/*   Updated: 2022/07/27 08:55:53 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// GERER OLDPWD

void	insert_node_after(t_envp *envp, char *after_name, t_envp *new)
{
	t_envp	*tmp;

	while (strncmp_len(envp->name, after_name) && envp)
		envp = envp->next;
	if (!strncmp_len(envp->name, after_name))
	{
		tmp = envp->next;
		envp->next = new;
		new->next = tmp;
	}
}

t_envp	*find_node(t_envp *envp, char *name)
{
	while (strncmp_len(envp->name, name) && envp)
	{
		if (envp->next)
			envp = envp->next;
		else
			break ;
	}
	if (!strncmp_len(envp->name, name))
		return (envp);
	return (NULL);
}

void	change_oldpwd(t_data_p *data, t_envp *envp, char *cwd)
{
	t_envp	*node;

	node = find_node(envp, "OLDPWD");
	if (node)
		node->content = gc_strdup(&data->track, cwd);
	else
	{
		insert_node_after(envp, "PWD", env_lstnew(data, "OLDPWD", cwd));
		node = find_node(envp, "OLDPWD");
		node->content = gc_strdup(&data->track, cwd);
	}
}

int	b_cd(t_data_p *data, int idx)
{
	char	*tmp;
	char	cwd[1016];

	getcwd(cwd, sizeof(cwd));
	chdir(data->commands[idx].args_vec[1]);
	change_oldpwd(data, data->envp, cwd);
	return (1);
}
