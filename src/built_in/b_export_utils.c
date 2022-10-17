/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:51:49 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 15:53:12 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_conditions(t_data *data, int idx)
{
	if (!arg_vec_len(data, idx) && data->pipes_nb > 0
		&& !data->commands[idx + 1].stop)
		print_export(data, data->envp, idx);
	else if (!arg_vec_len(data, idx)
		&& data->commands[idx].fd_out && !data->pipes_nb)
		print_export_fd_out(data, data->envp, idx);
	else if (!arg_vec_len(data, idx)
		&& data->commands[idx].fd_out && data->pipes_nb)
		print_export(data, data->envp, idx);
}
