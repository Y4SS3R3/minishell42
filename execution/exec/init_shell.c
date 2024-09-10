/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:11:29 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/10 08:45:36 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_shlvl(t_shell *data)
{
	char	*shlvl;
	char	*tmp;
	int		res;

	shlvl = get_var_value("SHLVL", data);
	if (!shlvl)
		return ;
	res = ft_atoi(shlvl);
	res++;
	tmp = ft_itoa(res, GLOBAL, data);
	if (tmp != NULL)
		return ;
	update_var(tmp, "SHLVL",
		search_fetch_list(data->envl, "SHLVL", data), data);
}

t_trash	*init_shell(t_shell *data, char **env)
{
	t_trash	*global;

	global = gc_new(NULL, data);
	if (global == NULL)
	{
		putstr_fd("Cannot open minishell : garbage collector failure[6345]\n", 2);
		exit(EXIT_FAILURE);
	}
	data->fork = 1;
	data->exapp = 0;
	data->envp = env;
	data->status = 0;
	data->cd_flag = 0;
	data->to_close = -1;
	data->add_equal = 1;
	data->fildes = NULL;
	data->last_arg = NULL;
	return (global);
}

void	init_shell_1(t_shell *data)
{
	char	*pwd;

	check_env(data);
	if (data->envp == NULL)
	{
		putstr_fd("Can't get shell environment\n", 2);
		exit(EXIT_FAILURE);
	}
	data->envl = env_parse(data->envp, data);
	update_shlvl(data);
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		gc_add(&data->g_gc, gc_new(pwd, data));
		update_var(pwd, "PWD",
			search_fetch_list(data->envl, "PWD", data), data);
		append_to_env("OLDPWD", NULL, 0, data);
	}
	else
	{
		putstr_fd("error retrieving current directory: ", 2);
		putstr_fd("getcwd: cannot access parent directories: \n", 2);
		perror("");
	}
	if (tcgetattr(STDERR_FILENO, &data->orig_termios) < 0)
	{
		perror("tcgetattr");
		data->status = 1;
		return ;
	}
}

t_trash	*init_l_gc(t_shell *data)
{
	t_trash	*loop;

	loop = gc_new(NULL, data);
	if (loop == NULL)
	{
		putstr_fd("Cannot open minishell : gc failed[6785]\n", 2);
		return (NULL);
	}
	return (loop);
}

void	init_path(t_shell *data)
{
	char	*tmp;

	data->envp = list_to_arr(data->envl, data);
	tmp = get_var_value("PWD", data);
	if (tmp)
		data->saved_path = tmp;
	check_potential_path(data);
}
