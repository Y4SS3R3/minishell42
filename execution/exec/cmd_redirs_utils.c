/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirs_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:08:55 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/04 16:13:35 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirs(t_token *root, t_shell *data)
{
	if (root->before)
	{
		if (handle_redirs(root->before, data, 1) == -1)
		{
			data->status = 1;
			return (1);
		}
	}
	if (root->after)
	{
		if (handle_redirs(root->after, data, 1) == -1)
		{
			data->status = 1;
			return (1);
		}
	}
	return (0);
}

int	redir_in(t_redir *in, t_shell *data)
{
	int	fd_in;

	(void)data;
	fd_in = -44;
	fd_in = open(in->file, O_RDONLY, 0644);
	if (fd_in == -1)
	{
		putstr_fd("starshell: ", 2);
		putstr_fd(in->file, 2);
		putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (fd_in);
}

int	heredoc_in(t_shell *data, int *flag, char **file, t_redir *node)
{
	int	fd_in;

	fd_in = -44;
	fd_in = heredocing_time_cmd(data, file, node);
	if (fd_in == -1)
		return (-1);
	*flag = 1;
	unlink(*file);
	return (fd_in);
}
