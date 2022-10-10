/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:42:35 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/10 14:42:51 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ncs = no case sensitive
int	strncmp_ncs(char *s1, char *s2)
{
	int	len;
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (ft_strlen(s1) < ft_strlen(s2))
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1);
	while (len > i && s1[i] && s2[i]
		&& (s1[i] == s2[i] || s1[i] == s2[i] + 32 || s1[i] == s2[i] - 32))
		i++;
	if (s1[i] == s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	if (s1[i] == s2[i] + 32)
		return ((unsigned char)s1[i] - (unsigned char)s2[i] + 32);
	if (s1[i] == s2[i] - 32)
		return ((unsigned char)s1[i] - (unsigned char)s2[i] - 32);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*find_node_content(char *name, t_envp *envp)
{
	if (envp)
	{
		while (envp)
		{
			if (!strncmp_len(envp->name, name))
				return (envp->content);
			envp = envp->next;
		}
	}
	return (NULL);
}

int	echo_arg_nb(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
		;
	return (i - 1);
}

void	get_in_out_init(int *i, int *j, int *in_type)
{
	*i = -1;
	*j = -1;
	*in_type = 0;
}

void	get_old_pwd_print(int x)
{
	if (x == 1)
		printf("cd: HOME not set\n");
	else if (x == 2)
		printf("cd: OLDPWD not set\n");
}
