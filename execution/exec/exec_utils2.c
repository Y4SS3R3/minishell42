/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:02:44 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/13 16:59:03 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ctrl_cmd(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit\n", 5);
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
		signal(SIGINT, ctrl_cmd);
		signal(SIGQUIT, ctrl_cmd);
		pid = fork();
		if (pid == -1)
		{
			putstr_fd("Fork() call failure\n", 2);
			return (1);
		}
		if (!pid)
			ft_exec(token, data);
	}
	return (pid);
}

void	update_status(t_shell *data)
{
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status)
		&& WTERMSIG(data->status) != SIGHUP)
		data->status = 128 + data->status;
}

void	check_ifdir(char *input, t_shell *data)
{
	DIR		*ret;

	if (input == NULL)
		return ;
	ret = opendir(input);
	if (ret)
	{
		putstr_fd("starshell: ", 2);
		putstr_fd(input, 2);
		putstr_fd(": is a directory\n", 2);
		improved_exit(126, data);
	}
	else
	{
		putstr_fd("starshell: ", 2);
		putstr_fd(input, 2);
		putstr_fd(": No such file or directory\n", 2);
		improved_exit(127, data);
	}
}

size_t	ft_strcmp_b(char *s1, char *s2)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && ft_tolower((unsigned char)s1[i])
		== ft_tolower((unsigned char)s2[i]))
		i++;
	return ((unsigned char)ft_tolower(s1[i])
		- (unsigned char)ft_tolower(s2[i]));
}
