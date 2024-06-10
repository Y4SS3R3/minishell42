/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:52:23 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 12:48:27 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_2d_array(char **arr)
{
	int i = 0;
	while (arr[i])
		printf("[%s]\n", arr[i++]);
}

void	ft_exec(t_token *token, t_shell *data)
{
	char *tmp;

	// dprintf(2, ">> CMD %s\n", token->cmd);
	tmp = token->cmd;
	if (data->to_close != -1)
		close(data->to_close);
	token->cmd = check_command(token->cmd, data->paths);
	print_2d_array(token->args);
	printf("PATH => %s\n", token->cmd);
	if (token->cmd == NULL)
		token->cmd = tmp;
	execve(token->cmd, token->args, data->envp);
	// gc_free(data);
	perror(token->cmd);
	exit(127);
}

int	exec_child(t_token *token, t_shell *data)
{
	int	pid;

	if (token->nature != WORD)
	{
		dfs_tree(token, data);
		return (-2);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			gc_free(data);
			putstr_fd("ERROR FORK[01]", 2);
			return (1);
		}
		if (!pid)
			ft_exec(token, data);
	}
	// while (wait(&data->status) != -1);
	return (pid);
}

void	update_status(t_shell *data)
{
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
}
