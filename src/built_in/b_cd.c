/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:51:37 by theodeville       #+#    #+#             */
/*   Updated: 2022/10/17 16:18:47 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	insert_node_after(t_envp **envp, char *after_name,
		t_envp *new, t_data *data)
{
	t_envp	*tmp;
	t_envp	*tmp1;

	tmp1 = *envp;
	if (!*envp && !strncmp_len(after_name, "PWD"))
	{
		env_lstadd_back(data, envp, new);
		return ;
	}
	while (strncmp_len(tmp1->name, after_name) && tmp1)
		tmp1 = tmp1->next;
	if (!strncmp_len(tmp1->name, after_name))
	{
		tmp = tmp1->next;
		tmp1->next = new;
		new->next = tmp;
	}
}

t_envp	*find_node(t_envp **envp, char *name)
{
	t_envp	*tmp;

	tmp = *envp;
	if (!tmp)
		return (NULL);
	while (strncmp_len(tmp->name, name) && tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (!strncmp_len(tmp->name, name))
		return (tmp);
	return (NULL);
}

void	change_oldpwd(t_data *data, t_envp **envp, char *cwd, int x)
{
	t_envp	*node;
	
	node = NULL;
	if (x == 1)
		add_node_oldpwd(data, envp, cwd, node);
	else if (x == 0)
	{
		node = find_node(envp, "PWD");
		if (node)
			node->content = gc_strdup(&data->track, cwd);
		else
		{
			insert_node_after(envp, "SHLVL",
				env_lstnew(data, "PWD", cwd, 1), data);
			node = find_node(envp, "PWD");
			node->content = gc_strdup(&data->track, cwd);
		}
	}
}

// Recupere la var HOME ou OLDPWD en fonction de x
char	*get_home_oldpwd(t_data *data, int x)
{
	t_envp	*tmp;

	tmp = data->envp;
	if (tmp)
	{
		while (tmp->next)
		{
			if (x == 1)
			{
				if (!strncmp_len(tmp->name, "HOME"))
					return (tmp->content);
			}
			else if (x == 2)
			{
				if (!strncmp_len(tmp->name, "OLDPWD"))
				{
					printf("%s\n", tmp->content);
					return (tmp->content);
				}
			}
			tmp = tmp->next;
		}
	}
	get_old_pwd_print(x);
	return (NULL);
}

int	b_cd(t_data *data, int idx)
{
	char	cwd[1016];

	getcwd(cwd, sizeof(cwd));
	if (!(*cwd) && !strncmp_len(data->commands[idx].args_vec[1], ".."))
		return (cd_error(data, cwd));
	if (chdir(data->commands[idx].args_vec[1]) == -1)
	{
		if (!data->commands[idx].args_vec[1])
			chdir(get_home_oldpwd(data, 1));
		else
		{
			g_status = 1;
			printf("cd: %s: No such file or directory\n",
				data->commands[idx].args_vec[1]);
		}
	}
	change_oldpwd(data, &data->envp, cwd, 1);
	getcwd(cwd, sizeof(cwd));
	change_oldpwd(data, &data->envp, cwd, 0);
	return (1);
}
