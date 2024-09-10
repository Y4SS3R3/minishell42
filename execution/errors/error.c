/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:44:55 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/10 20:24:26 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	stop_programm(t_shell *data)
{
	close_fildes(data);
	free_command(data, NULL);
	free_programm(data);
	exit(EXIT_FAILURE);
}

void	fds_error(t_shell *data, char *msg)
{
	putstr_fd(msg, 2);
	data->status = 1;
	close_fildes(data);
}
