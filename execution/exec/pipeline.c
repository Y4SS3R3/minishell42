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

static int	redir_pipe(t_shell *data, t_token *token, int fd1, int fd2)
{
	int	tmp;
	int	pid;

	tmp = dup(fd2);
	if (tmp == -1)
		error_protocole("DUP() ERROR[00]\n", data, EXIT_FAILURE);
	dup2_plus(fd1, fd2, data);
	pid = exec_child(token, data);
	dup2_plus(tmp, fd2, data);
	return (pid);
}

int  pipe_line(t_token *token, t_shell *data)
{
    int p_fd[2];
    int pid1 = -111;
    int pid2 = -111;
    int tmp;

	data->index++;
	if (pipe(p_fd) == -1)
	return (putstr_fd("ERROR IN PIPE OPENING[01]", 2), -1);
	data->to_close = p_fd[READ];
	tmp = dup(1);
	dup2(p_fd[WRITE], 1);
	close(p_fd[WRITE]);
	pid1 = exec_child(token->left, data);
	dup2(tmp, 1);
	close(tmp);
	tmp = dup(0);
	dup2(p_fd[READ], 0);
	close(p_fd[READ]);
	data->to_close = -1;
	pid2 = exec_child(token->right, data);
	dup2(tmp, 0);
	close(tmp);
	if (pid1 != -2)
		waitpid(pid1, NULL, 0);
	if (pid2 != -2)
		waitpid(pid2, &data->status, 0);
	update_status(data);
	dup2(data->def_in, 0);
	dup2(data->def_out, 1);
	// data->index--;
	return (-2);
}
