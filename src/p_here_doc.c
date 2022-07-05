/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:04:51 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/05 15:33:13 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ----------------------- CHECK HERE DOC AND GET DEL -----------------------

int	check_heredoc(char *arg, t_data_p *data, int idx)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '<' && arg[i + 1] == '<')
		{
			get_heredoc_del(arg, i + 2, data);
			ft_here_doc(data, idx);
			// clear_here_doc(data, arg);
		}
		i++;
	}
	return (0);
}

int	get_heredoc_del(char *arg, int i, t_data_p *data)
{
	int		j;
	int		quote;

	quote = 0;
	data->hd_data.expend_var = 1;
	while (arg[i] == ' ' && arg[i])
		i++;
	j = i;
	while (arg[i] != ' ' && arg[i] != '<' && arg[i])
	{
		if ((arg[i] == '\"' || arg[i] == '\''))
		{
			data->hd_data.expend_var = 0;
			quote = 1;
		}
		i++;
	}
	data->hd_data.here_doc_del = gc_substr(&data->track, arg, j, (i - j));
	if (quote != 0)
		format_del(data->hd_data.here_doc_del, data);
	return (0);
}

int	format_del(char *del, t_data_p *data)
{
	int		i;
	int		j;
	char	quote;
	char	*new_del;
	
	i = -1;
	j = 0;
	quote = 0;
	new_del = gc_calloc(sizeof(char), (ft_strlen(del) + 1), &data->track);
	while (del[++i])
	{
		if ((del[i] == '\'' || del[i] == '\"') && quote == 0)
			quote = del[i++];
		if (del[i] == quote && quote != 0)
		{
			quote = 0;
			i++;
		}
		if ((del[i] == '\'' || del[i] == '\"') && quote == 0)
			continue ;
		else
			new_del[j] = del[i];
		j++;
	}
	data->hd_data.here_doc_del = gc_strdup(&data->track, new_del);
	return (0);
}

// -------------------------- HERE DOC --------------------------

int	ft_here_doc(t_data_p *data, int idx)
{
	int		del_len;
	int		longest;
	char	*buffer;
	
	data->commands[idx].here_doc = NULL;
	del_len = ft_strlen(data->hd_data.here_doc_del);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		buffer = gc_get_next_line(&data->track, STDIN_FILENO);
		longest = del_len;
		if (ft_strlen(buffer) > (size_t)del_len)
			longest = (ft_strlen(buffer) - 1);
		if (!ft_strncmp(buffer
			, data->hd_data.here_doc_del, longest))
			break;
		here_doc_write(data, buffer, idx);
		gc_free_malloc(&data->track, (void **)&buffer);
	}
	gc_free_malloc(&data->track, (void **)&buffer);
	if (data->commands[idx].here_doc)
		data->commands[idx].here_doc = trim_last_bsn(data, data->commands[idx].here_doc);
	return (0);
}

int	here_doc_write(t_data_p *data, char *buffer, int idx)
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

char	*get_expend_var(t_data_p *data, char *buffer)
{
	int		i;
	int		k;
	char	**vars;
	char	*tmp;

	i = -1;
	k = 0;
	vars = gc_calloc(sizeof(char *), (nb_of_env_vars(buffer) + 1), &data->track);
	while (buffer[++i])
		if (buffer[i] == '$')
			fill_vars_tab(data, &vars[k], buffer, &i, &k);
	vars[k] = 0;
	i = 0;
	if (vars)
	{
		while (vars[i])
		{
			tmp = vars[i];
			vars[i] = expend_env_var(data, data->env_vars, vars[i]);
			if (!ft_strncmp(vars[i], tmp, ft_strlen(vars[i])))
				vars[i] = gc_strjoin(&data->track, "$", tmp);
			i++;
		}
	}
	return (expend_var_in_buffer(buffer, vars, data));
}

void	fill_vars_tab(t_data_p *data, char **var, char *buffer, int *idx, int *k)
{
	int	j;
	int	check;

	j = *idx;
	check = 0;
	while (buffer[*idx] != ' ' && buffer[*idx])
	{
		if (buffer[*idx] == '\n' || buffer[*idx] == '\'' || buffer[*idx] == '\"')
			break ;
		(*idx)++;
		if (buffer[*idx] == '$')
		{
			check = 1;
			break ;
		}
	}
	*var = gc_substr(&data->track, buffer, j + 1, (*idx - j) - 1);
	(*k)++;
	if (check == 1)
		(*idx)--;
}

char	*expend_var_in_buffer(char *buffer, char **expended_vars, t_data_p *data)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 0;
	data->hd_data.new_buffer = 0;
	data->hd_data.tmp = 0;
	data->hd_data.tmp1 = 0;
	data->hd_data.check = 0;
	while (buffer[++i])
	{
		j = i;
		while (buffer[i] != '$' && buffer[i])
			i++;
		if (i > 0)
		{
			data->hd_data.tmp = gc_substr(&data->track, buffer, j, (i - j));
			if (expended_vars[k] && check_var(expended_vars[k]))
				data->hd_data.tmp1 = gc_strjoin(&data->track, data->hd_data.tmp, expended_vars[k++]);
			else if (expended_vars[k] && !check_var(expended_vars[k]))
			{
				data->hd_data.tmp1 = gc_strdup(&data->track, data->hd_data.tmp);
				data->hd_data.check = 1;
				k++;
			}
			else if (!expended_vars[k])
				data->hd_data.tmp1 = gc_strdup(&data->track, data->hd_data.tmp);
		}
		else if (i == 0)
		{
			if (expended_vars[k] && check_var(expended_vars[k]))
				data->hd_data.tmp1 = gc_strdup(&data->track, expended_vars[k++]);
			else if (expended_vars[k] && !check_var(expended_vars[k]))
			{
				data->hd_data.check = 1;
				k++;
			}
		}
		while (buffer[i])
		{
			if (data->hd_data.check == 1 && (buffer[i + 1] == '\'' 
				|| buffer[i + 1] == '\"'))
			{
				data->hd_data.check = 0;
				break ;
			}
			if (buffer[i + 1] == ' ' || buffer[i + 1] == '$'
				|| buffer[i + 1] == '\'' || buffer[i + 1] == '\"')
				break ;
			i++;
		}
		if (!data->hd_data.new_buffer && data->hd_data.tmp1)
			data->hd_data.new_buffer = gc_strdup(&data->track, data->hd_data.tmp1);
		else if (!data->hd_data.new_buffer && !data->hd_data.tmp1)
			continue ;
		else
			data->hd_data.new_buffer = gc_strjoin(&data->track, data->hd_data.new_buffer, data->hd_data.tmp1);
	}
	data->hd_data.new_buffer = check_bsn_buffer(data, data->hd_data.new_buffer);
	return (data->hd_data.new_buffer);
}
