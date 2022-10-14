/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:04:51 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/14 20:16:50 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

// -------------------------- HERE DOC --------------------------
int	ft_here_doc(t_data *data, int idx)
{
	int		pid;
	int		pipehd[2];
	int status;

	pipe(pipehd);
	signal(SIGINT, sig_handler_parent_hd);
	pid = fork();
	if (pid == 0)
	{
		sig_child();
		data->commands[idx].here_doc = NULL;
		while (1)
			if (hd_loop(data, idx))
				break ;
		close(pipehd[0]);
		write(pipehd[1], data->commands[idx].here_doc,
			ft_strlen(data->commands[idx].here_doc));
		close(pipehd[1]);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (!WIFSIGNALED(status))
		g_status = WEXITSTATUS(status);
	close(pipehd[1]);
	data->commands[idx].here_doc = get_pipe_content(pipehd[0], data);
	close(pipehd[0]);
	return (0);
}

int	here_doc_write(t_data *data, char *buffer, int idx)
{
	if (data->hd_data.expend_var)
		buffer = get_expend_var(data, buffer);
	if (!data->commands[idx].here_doc)
		data->commands[idx].here_doc = gc_strdup(&data->track, buffer);
	else
	{
		data->commands[idx].here_doc = gc_strjoin
			(&data->track, data->commands[idx].here_doc, buffer);
	}
	return (0);
}

// Cette fonction recupere les variable d'env
// dans le buffer du here_doc et les met dans un tabl vars
// a laide de la fonction fill_vars_tab
// Ensuite on boucle sur le tableau et on expend les variables
// existantes grace a la fonction expend_env_var
char	*get_expend_var(t_data *data, char *buffer)
{
	t_hd_data	hdd;
	char		**vars;
	char		*tmp;

	hdd.i = -1;
	hdd.k = 0;
	vars = gc_calloc(sizeof(char *),
			(nb_of_env_vars(buffer) + 1), &data->track);
	while (buffer[++hdd.i])
		if (buffer[hdd.i] == '$')
			fill_vars_tab(data, &vars[hdd.k], buffer, &hdd);
	vars[hdd.k] = 0;
	hdd.i = -1;
	if (vars)
	{
		while (vars[++hdd.i])
		{
			tmp = vars[hdd.i];
			vars[hdd.i] = expend_env_var(data->envp, vars[hdd.i]);
			if (!ft_strncmp(vars[hdd.i], tmp, ft_strlen(vars[hdd.i])))
				vars[hdd.i] = gc_strjoin(&data->track, "$", tmp);
		}
	}
	return (expend_var_in_buffer(buffer, vars, data));
}

// Cette fonction permet de remplire les cases du tableau vars crée
// dans la fonction get_expended_var avec toutes les variables d'environnement
// Exemple: [0] = "USER", [1] = "PATH", [2] = "non"
// Suite a quoi dans on join le dollard 
// dans la deuxieme partie de get_expend_var
void	fill_vars_tab(t_data *data, char **var,
		char *buffer, t_hd_data *hdd)
{
	int	j;
	int	check;

	j = hdd->i;
	check = 0;
	while (buffer[hdd->i] != ' ' && buffer[hdd->i])
	{
		if (buffer[hdd->i] == '\n' || buffer[hdd->i] == ' ')
			break ;
		(hdd->i)++;
		if (buffer[hdd->i] == '$' || !ft_isalnum(buffer[hdd->i]))
		{
			check = 1;
			break ;
		}
	}
	*var = gc_substr(&data->track, buffer, j + 1, (hdd->i - j) - 1);
	(hdd->k)++;
	if (check == 1)
		(hdd->i)--;
}
