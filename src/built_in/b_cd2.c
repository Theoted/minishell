/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:28:13 by rmattheo          #+#    #+#             */
/*   Updated: 2022/10/17 16:04:51 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_node_oldpwd(t_data *data, t_envp **envp, char *cwd, t_envp *node)
{
	node = find_node(envp, "OLDPWD");
	if (node)
		node->content = gc_strdup(&data->track, cwd);
	else
	{
		insert_node_after(envp, "PWD",
			env_lstnew(data, "OLDPWD", cwd, 1), data);
		node = find_node(envp, "OLDPWD");
		node->content = gc_strdup(&data->track, cwd);
	}
}

int	cd_error(t_data *data, char *cwd)
{
	perror("cd: error retrieving current directory:"
		"getcwd: cannot access parent directories");
	change_oldpwd(data, &data->envp, cwd, 1);
	chdir(get_home_oldpwd(data, 1));
	getcwd(cwd, sizeof(cwd));
	change_oldpwd(data, &data->envp, cwd, 0);
	return (1);
}
