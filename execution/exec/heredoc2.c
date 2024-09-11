/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:33:20 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/11 15:30:16 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*fill_heredoc(char *limiter, t_shell *data)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	if (line == NULL || g_sig)
		return (NULL);
	if (!ft_strcmp(line, limiter))
	{
		free(line);
		return (NULL);
	}
	tmp = ft_strjoin(line, "\n", LOOP, data);
	free(line);
	return (tmp);
}

int	open_hdc(char *file, t_fd *node, t_shell *data)
{
	int	hdc;

	node->file_name = file;
	hdc = open(file, O_CREAT | O_RDWR, 0644);
	if (hdc == -1)
	{
		putstr_fd("Open() call failed[719]\n", 2);
		close_fildes(data);
		return (-1);
	}
	data->fildes = append_fdes(data, hdc);
	return (hdc);
}

int	hrdc_ctrlc(int fd, t_shell *data)
{
	if (g_sig)
	{
		data->status = 1;
		data->exec = 0;
		if (dup2(fd, 0) == -1)
		{
			fds_error(data, "Dup2() call failure[717]\n");
			return (CTRLC_HRDC);
		}
		close(fd);
		return (CTRLC_HRDC);
	}
	return (0);
}

int	end_hdc(int fd, char *file, t_shell *data)
{
	int	hdc;

	close(fd);
	hdc = open(file, O_CREAT | O_RDWR, 0644);
	if (hdc == -1)
	{
		putstr_fd("Open() call failed[013]\n", 2);
		close_fildes(data);
		unlink(file);
		return (-1);
	}
	data->fildes = append_fdes(data, hdc);
	unlink(file);
	return (hdc);
}
