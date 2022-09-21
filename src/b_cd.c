/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:51:37 by theodeville       #+#    #+#             */
/*   Updated: 2022/09/21 16:03:07 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_node_after(t_envp **envp, char *after_name, t_envp *new, t_data_p *data)
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
	if (!*envp)
		return (NULL);
	while (strncmp_len((*envp)->name, name) && *envp)
	{
		if ((*envp)->next)
			*envp = (*envp)->next;
		else
			break ;
	}
	if (!strncmp_len((*envp)->name, name))
		return (*envp);
	return (NULL);
}

void	change_oldpwd(t_data_p *data, t_envp **envp, char *cwd)
{
	t_envp	*node;

	node = find_node(envp, "OLDPWD");
	if (node)
		node->content = gc_strdup(&data->track, cwd);
	else
	{
		insert_node_after(envp, "PWD", env_lstnew(data, "OLDPWD", cwd), data);
		node = find_node(envp, "OLDPWD");
		node->content = gc_strdup(&data->track, cwd);
	}
}

// Recupere la var HOME ou OLDPWD en fonction de x
char	*get_home_oldpwd(t_data_p *data, int x)
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
	if (x == 1)
		printf("cd: HOME not set\n");
	else if (x == 2)
		printf("cd: OLDPWD not set\n");
	return (NULL);
}

int	b_cd(t_data_p *data, int idx)
{
	char	*tmp;
	char	cwd[1016];

	getcwd(cwd, sizeof(cwd));
	if (chdir(data->commands[idx].args_vec[1]) == -1)
	{
		if (!data->commands[idx].args_vec[1]
			|| !strncmp_len(data->commands[idx].args_vec[1], "~"))
			chdir(get_home_oldpwd(data, 1));
		else if (!strncmp_len(data->commands[idx].args_vec[1], "-"))
			chdir(get_home_oldpwd(data, 2));
		else
			printf("cd: %s: No such file or directory\n",
				data->commands[idx].args_vec[1]);
	}
	change_oldpwd(data, &data->envp, cwd);
	return (1);
}
