/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tfg                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:37:54 by ymassiou          #+#    #+#             */
/*   Updated: 2024/05/22 20:15:54 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	pipe_line2(int read_end, int pid1, t_token *token, t_shell *data)
{
	int	tmp;
	int	pid2;

	tmp = dup(0);
	if (tmp == -1)
		return (fds_error(data, "Dup() call failure[092]\n"), -1);
	append_fdes(data, tmp);
	if (!is_a_redir(token->right))
	{
		if (dup2(read_end, 0) == -1)
			return (fds_error(data, "Dup2() call failure[797]\n"), -1);
	}
	close(read_end);
	data->to_close = -1;
	pid2 = exec_child(token->right, data);
	if (dup2(tmp, 0) == -1)
		return (fds_error(data, "Dup2() call failure[797]\n"), -1);
	close(tmp);
	if (pid1 != -2)
		waitpid(pid1, NULL, 0);
	if (pid2 != -2)
		waitpid(pid2, &data->status, 0);
	update_status(data);
	return (0);
}

static int	pipe_line1(int write_end, t_token *token, t_shell *data)
{
	int	tmp;
	int	pid1;

	pid1 = -111;
	tmp = dup(1);
	if (tmp == -1)
		return (fds_error(data, "Dup() call failure[027]\n"), -1);
	append_fdes(data, tmp);
	if (!is_a_redir(token->left))
	{
		if (dup2(write_end, 1) == -1)
			return (fds_error(data, "Dup2() call failure[668]\n"), -1);
	}
	close(write_end);
	pid1 = exec_child(token->left, data);
	if (dup2(tmp, 1) == -1)
		return (fds_error(data, "Dup2() call failure[618]\n"), -1);
	close(tmp);
	return (pid1);
}

void	pipe_line(t_token *token, t_shell *data)
{
	int	p_fd[2];
	int	pid1;

	pid1 = -111;
	if (pipe(p_fd) == -1)
	{
		fds_error(data, "Pipe() call failure[017]\n");
		return ;
	}
	append_fdes(data, p_fd[READ]);
	append_fdes(data, p_fd[WRITE]);
	data->to_close = p_fd[READ];
	pid1 = pipe_line1(p_fd[WRITE], token, data);
	if (pipe_line2(p_fd[READ], pid1, token, data))
		return ;
	return ;
}
