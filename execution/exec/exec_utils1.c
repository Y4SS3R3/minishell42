/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:52:23 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/11 11:03:38 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ex_copy(t_fd *node, int tmp, t_shell *data)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = node->fd;
	line = get_next_line(fd, data);
	if (line == NULL)
		return (-1);
	if (node->ex_flag)
	{
		line = ex_key_2_assign(line, data->key, data);
		if (ft_strnstr(line, data->key, ft_strlen(line)))
			line = ex_assign(line, data->key, data);
	}
	write(tmp, line, ft_strlen(line));
	return (0);
}

int	ex_heredoc(t_fd *node, char **new_file, t_shell *data)
{
	char	*name;
	int		tmp;

	name = randomize_file_name(data);
	name = ft_strjoin(name, "_tmp", LOOP, data);
	tmp = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp == -1)
		return (fds_error(data, "Open() call failed[409]\n"), -1);
	data->fildes = append_fdes(data, tmp);
	data->filcollect = ft_strjoin(data->filcollect, name, LOOP, data);
	data->filcollect = ft_strjoin(data->filcollect, ".", LOOP, data);
	while (1)
	{
		if (ex_copy(node, tmp, data))
			break ;
	}
	close(node->fd);
	close(tmp);
	*new_file = name;
	tmp = open(name, O_CREAT | O_RDWR, 0644);
	if (tmp == -1)
		return (fds_error(data, "Open() call failed[215]\n"), -1);
	data->fildes = append_fdes(data, tmp);
	return (tmp);
}

static void	execute_cmd(t_token *token, t_shell *data)
{
	char	*tmp;

	if (!token->cmd)
		exit(0);
	tmp = check_command(token->cmd, data->paths, data);
	data->flag = 3;
	token->args = mz_arr(token->args, NULL, tmp, data);
	execve(tmp, token->args, data->envp);
	exec_err1(tmp, data);
	rl_clear_history();
	close_fildes(data);
	unlink_fil(data);
	free_command(data, NULL);
	exit(127);
}

static void	ft_expand_in_cmd(t_token *token, t_shell *data)
{
	int		ret;

	ret = ft_expand(token, data);
	if (ret != 0)
	{
		if (!data->show_err)
			putstr_fd("starshell: ambiguous redirect\n", 2);
		improved_exit(1, data);
	}
}

void	ft_exec(t_token *token, t_shell *data)
{
	char	*tmp;

	if (data->to_close != -1)
		close(data->to_close);
	ft_expand_in_cmd(token, data);
	tmp = token->cmd;
	if (token->before)
	{
		if (handle_redirs(token->before, data, 1) == -1)
			improved_exit(EXIT_FAILURE, data);
	}
	if (token->after)
	{
		if (handle_redirs(token->after, data, 1) == -1)
			improved_exit(EXIT_FAILURE, data);
	}
	if (is_a_builtin(token))
		improved_exit(execute_builtin(token, data), data);
	else
		execute_cmd(token, data);
}
