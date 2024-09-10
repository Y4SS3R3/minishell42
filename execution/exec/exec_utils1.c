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
	line = get_next_line(fd);
	if (line == NULL)
		return (-1);
	gc_add(&data->l_gc, gc_new(line, data));
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

static void	execute_cmd(char *tmp, t_token *token, t_shell *data)
{
	if (ft_strcmp(token->cmd, "")
		&& ft_strcmp(token->cmd, ".") && ft_strcmp(token->cmd, ".."))
		token->cmd = check_command(token->cmd, data->paths, data);
	else if (!ft_strcmp(token->cmd, "."))
	{
		putstr_fd("starshell: dot sourcing not supported.\n", 2);
		exit (2);
	}
	else if (!ft_strcmp(token->cmd, ".."))
	{
		putstr_fd("starshell: ..: command not found\n", 2);
		exit (127);
	}
	token->args = mz_arr(token->args, NULL, token->cmd, 3, data);
	execve(token->cmd, token->args, data->envp);
	if (token->cmd)
		check_ifdir(token);
	putstr_fd("starshell: ", 2);
	putstr_fd(tmp, 2);
	putstr_fd(": command not found\n", 2);
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
		exit(1);
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
			exit(EXIT_FAILURE);
	}
	if (token->after)
	{
		if (handle_redirs(token->after, data, 1) == -1)
			exit(EXIT_FAILURE);
	}
	if (is_a_builtin(token))
		exit(execute_builtin(token, data));
	else
		execute_cmd(tmp, token, data);
}
