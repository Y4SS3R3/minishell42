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

void	pipe_line2(int read_end, int pid1, t_token *token, t_shell *data)
{
	int	tmp;
	int	pid2;

	tmp = dup(0);
	if (!is_a_redir(token->right))
		dup2(read_end, 0);
	close(read_end);
	data->to_close = -1;
	pid2 = exec_child(token->right, data);
	dup2(tmp, 0);
	close(tmp);
	if (pid1 != -2)
		waitpid(pid1, NULL, 0);
	if (pid2 != -2)
		waitpid(pid2, &data->status, 0);
	update_status(data);
}

int	pipe_line(t_token *token, t_shell *data)
{
	int	p_fd[2];
	int	pid1;
	int	tmp;

	data->index++;
	pid1 = -111;
	if (pipe(p_fd) == -1)
		return (putstr_fd("ERROR IN PIPE OPENING[01]", 2), -1);
	data->to_close = p_fd[READ];
	tmp = dup(1);
	if (!is_a_redir(token->left))
		dup2(p_fd[WRITE], 1);
	close(p_fd[WRITE]);
	pid1 = exec_child(token->left, data);
	dup2(tmp, 1);
	close(tmp);
	pipe_line2(p_fd[READ], pid1, token, data);
	return (-2);
}
