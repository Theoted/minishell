/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_synthax_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:09:49 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 17:23:38 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	pipe_check(char *arg, int i)
{
	char	quote;
	int		j;

	quote = 0;
	j = 0;
	while (j < i)
	{
		if ((arg[j] == '\'' || arg[j] == '\"') && quote == 0)
			quote = arg[j];
		else if (arg[j] == quote && quote)
			quote = 0;
		j++;
	}
	if (quote)
		return (1);
	return (0);
}

int	pipe_synthax(char *str, t_data data)
{
	int	i;
	int	valid_pipe_nb;

	i = 0;
	valid_pipe_nb = 0;
	while (str[i])
	{
		if (str[i] == '|' && (!pipe_check(str, i)))
			valid_pipe_nb++;
		if (str[i] == '|' && (!pipe_check(str, i))
			&& valid_pipe_nb == data.pipes_nb)
		{
			while (str[++i])
				if (ft_isalpha(str[i]))
					return (1);
		}
		i++;
	}
	return (0);
}

// check le cas du >>>
int	check_chevrons(char *arg, int *i)
{
	if (arg[*i + 1] == '>' && arg[*i + 2] == '>')
	{
		printf("Chevrons: Syntax error\n");
		g_status = 1;
		return (1);
	}
	if (arg[*i + 1] == '>' && arg[*i + 2] != '>')
		(*i)++;
	return (0);
}

// Return 0 si il y a du contenu apres un pipe. Sinon return 1
int	check_content_after_pipe(char *arg, int i)
{
	while (arg[++i])
	{
		if (arg[i] == '|')
			break ;
		if ((arg[i] >= 33 && arg[i] <= 125)
			|| (arg[i] >= 125 && arg[i] <= 126))
			return (0);
	}
	printf("Pipe: Syntax error\n");
	g_status = 258;
	return (1);
}

int	synthax_checker(char *arg)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	if (check_space(arg))
		return (printf("Synthax Error\n"));
	while (arg[++i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && quote == 0)
			quote = arg[i];
		else if (arg[i] == quote && quote)
			quote = 0;
		else if (arg[i] == '|' && quote == 0)
		{
			if (check_content_after_pipe(arg, i))
				return (1);
		}
		else if (arg[i] == '>')
			if (check_chevrons(arg, &i))
				return (1);
	}
	return (quote_check_return(quote));
}
