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

int	pipe_line2(int read_end, int pid1, t_token *token, t_shell *data)
{
	int	tmp;
	int	pid2;

	tmp = dup(0);
	if (tmp == -1)
	{
		putstr_fd("Dup() call failure[092]\n", 2);
		data->status = 1;
		close(read_end);
		close_fildes(data);
		return (-1);
	}
	if (!is_a_redir(token->right))
	{
		if (dup2(read_end, 0) == -1)
		{
			putstr_fd("Dup2() call failure[797]\n", 2);
			data->status = 1;
			close(read_end);
			close(tmp);
			close_fildes(data);
			return (-1);
		}
	}
	close(read_end);
	data->to_close = -1;
	pid2 = exec_child(token->right, data);
	if (dup2(tmp, 0) == -1)
	{
		putstr_fd("Dup2() call failure[606]\n", 2);
		data->status = 1;
		close(tmp);
		close_fildes(data);
		return (-1);
	}
	close(tmp);
	if (pid1 != -2)
		waitpid(pid1, NULL, 0);
	if (pid2 != -2)
		waitpid(pid2, &data->status, 0);
	update_status(data);
	return (0);
}

void	pipe_line(t_token *token, t_shell *data)
{
	int	p_fd[2];
	int	pid1;
	int	tmp;

	data->index++;
	pid1 = -111;
	if (pipe(p_fd) == -1)
	{
		putstr_fd("Pipe() call failure[017]\n", 2);
		data->status = 1;
		close_fildes(data);
		return ;
	}
		// return (putstr_fd("ERROR IN PIPE OPENING[01]", 2), -1);
	data->to_close = p_fd[READ];
	tmp = dup(1);
	if (tmp == -1)
	{
		putstr_fd("Dup() call failure[027]\n", 2);
		data->status = 1;
		close(p_fd[0]);
		close(p_fd[1]);
		close_fildes(data);
		return ;
	}
	if (!is_a_redir(token->left))
	{
		if (dup2(p_fd[WRITE], 1) == -1)
		{
			putstr_fd("Dup2() call failure[668]\n", 2);
			data->status = 1;
			close(tmp);
			close(p_fd[WRITE]);
			close(p_fd[READ]);
			close_fildes(data);
			return ;
		}
	}
	close(p_fd[WRITE]);
	pid1 = exec_child(token->left, data);
	if (dup2(tmp, 1) == -1)
	{
		putstr_fd("Dup2() call failure[618]\n", 2);
		data->status = 1;
		close(tmp);
		close(p_fd[READ]);
		close_fildes(data);
		return ;
	}
	close(tmp);
	if (pipe_line2(p_fd[READ], pid1, token, data))
		return ;
	return ;
}
