/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:11:29 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/30 18:40:11 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_shlvl(t_shell *data)
{
	char	*shlvl;
	char	*tmp1;
	int		res;

	shlvl = get_var("SHLVL", data);
	res = ft_atoi(shlvl);
	res++;
	tmp1 = ft_itoa(res, GLOBAL, data);
	update_var(tmp1, "SHLVL",
		search_fetch_list(data->envl, "SHLVL", data), data);
}

t_trash	*init_shell(t_shell *data, char **env)
{
	t_trash	*global;

	global = gc_new(NULL, data);
	if (global == NULL)
	{
		putstr_fd("CANNOT OPEN MINISHELL : GC FAILED[6345]\n", 2);
		exit(EXIT_FAILURE);
	}
	data->to_close = -1;
	data->status = 0;
	data->fork = 1;
	data->add_equal = 1;
	data->cd_flag = 0;
	data->exapp = 0;
	data->envp = env;
	data->fildes = NULL;
	data->last_arg = NULL;
	return (global);
}

void	init_shell_1(t_shell *data)
{
	char	*pwd;

	check_env(data);
	data->envl = env_parse(data->envp, data);
	update_shlvl(data);
	pwd = getcwd(NULL, 0);
	if (tcgetattr(STDERR_FILENO, &data->orig_termios) < 0)
	{
		perror("tcgetattr");
		data->status = 1;
		return ;
	}
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
}

t_trash	*init_l_gc(t_shell *data)
{
	t_trash	*loop;

	(void)data;
	loop = gc_new(NULL, data);
	if (loop == NULL)
	{
		putstr_fd("CANNOT OPEN MINISHELL : GC FAILED[6785]\n", 2);
		exit(EXIT_FAILURE);
	}
	return (loop);
}

void	init_path(t_shell *data)
{
	char	*tmp;

	data->envp = list_to_arr(data->envl, data);
	tmp = get_var("PWD", data);
	if (tmp)
		data->saved_path = tmp;
	check_potential_path(data);
}
