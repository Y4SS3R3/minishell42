/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:44:55 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/10 16:43:33 by ymassiou         ###   ########.fr       */
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

int	improved_dup2(int fd1, int fd2, t_shell *data)
{
	if (dup2(fd1, fd2) == -1)
	{
		fds_error(data, "Dup2() call failure[110]\n");
		return -1;
	}
	if (dup2(fd1, fd2) == -1)
	{
		fds_error(data, "Dup2() call failure[169]\n");
		return -1;
	}
	return (0);
}
