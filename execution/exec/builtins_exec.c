/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:24:58 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/10 16:43:33 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_a_builtin(t_token *node)
{
	if (!ft_strcmp_b(node->cmd, "cd")
		|| !ft_strcmp_b(node->cmd, "echo")
		|| !ft_strcmp_b(node->cmd, "env")
		|| !ft_strcmp_b(node->cmd, "exit")
		|| !ft_strcmp_b(node->cmd, "unset")
		|| !ft_strcmp_b(node->cmd, "export")
		|| !ft_strcmp_b(node->cmd, "pwd"))
		return (1);
	return (0);
}

static int	bring_std_back(int def_in, int def_out, t_shell *data)
{
	if (dup2(def_in, 0) == -1)
	{
		fds_error(data, "Dup2() call failure[110]\n");
		return (-1);
	}
	if (dup2(def_out, 1) == -1)
	{
		fds_error(data, "Dup2() call failure[169]\n");
		return (-1);
	}
	return (0);
}

static int	save_fds(int *def_in, int *def_out, t_shell *data)
{
	*def_in = dup(0);
	if (*def_in == -1)
	{
		fds_error(data, "Dup() call failure[912]\n");
		return (-1);
	}
	append_fdes(data, *def_in);
	*def_out = dup(1);
	if (*def_out == -1)
	{
		fds_error(data, "Dup() call failure[612]\n");
		return (-1);
	}
	append_fdes(data, *def_out);
	return (0);
}

void	handle_builtin(t_token *root, t_shell *data)
{
	int	def_in;
	int	def_out;

	save_fds(&def_in, &def_out, data);
	if (expand(root, data))
	{
		close(def_in);
		close(def_out);
		return ;
	}
	if (redirs(root, data) == 0)
		data->status = execute_builtin(root, data);
	if (bring_std_back(def_in, def_out, data) == -1)
		return ;
	close(def_in);
	close(def_out);
}

int	execute_builtin(t_token *token, t_shell *data)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp_b(token->cmd, "cd"))
		ret = cd(get_length(token->args), token->args, data);
	else if (!ft_strcmp_b(token->cmd, "pwd"))
		ret = pwd(data);
	else if (!ft_strcmp_b(token->cmd, "echo"))
		ret = echo(get_length(token->args), token->args);
	else if (!ft_strcmp_b(token->cmd, "unset"))
		ret = unset(get_length(token->args), token->args, data);
	else if (!ft_strcmp_b(token->cmd, "export"))
		ret = export(get_length(token->args), token->args, data);
	else if (!ft_strcmp_b(token->cmd, "exit"))
		ret = exit_cmd(get_length(token->args), token->args, data);
	else if (!ft_strcmp_b(token->cmd, "env"))
		ret = env(data);
	data->status = ret;
	return (ret);
}
