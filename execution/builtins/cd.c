/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:50:32 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:56:32 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	cd_home(t_shell *data)
{
	char	*home;
	char	*currpwd;

	home = search_fetch_add(data->envp, "HOME", data);
	if (home == NULL)
		return (putstr_fd("starshell: cd: HOME not set\n", 2), 1);
	else
	{
		if (chdir(home + 5))
			return (perror(NULL), 1);
		else
		{
			currpwd = getcwd(NULL, 0);
			gc_add(&data->l_gc, gc_new(currpwd, data));
			if (currpwd == NULL)
				currpwd = get_var_value("PWD", data);
			update_pwd(currpwd, data);
		}
	}
	return (0);
}

static void	cd_part2(t_shell *data, char *path)
{
	char	*currpwd;

	currpwd = getcwd(NULL, 0);
	gc_add(&data->l_gc, gc_new(currpwd, data));
	if (currpwd == NULL)
	{
		currpwd = get_var_value("PWD", data);
		if (!ft_strcmp(path, ".."))
			currpwd = join_chdir(currpwd, "/..", data);
		if (!ft_strcmp(path, "."))
			currpwd = join_chdir(currpwd, "/.", data);
		data->status = 1;
	}
	cd_custompath(currpwd, path, data);
}

int	cd(int ac, char **av, t_shell *data)
{
	char	*tmp;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	gc_add(&data->l_gc, gc_new(oldpwd, data));
	tmp = get_var_value("PWD", data);
	if (tmp)
		data->saved_path = tmp;
	else
		data->saved_path = oldpwd;
	if (ac == 0)
		return (cd_home(data));
	if (ft_strlen(av[0]))
	{
		if (!ft_strcmp(av[0], "~"))
			return (cd_home(data));
		if (chdir(av[0]) != 0)
		{
			perror(av[0]);
			return (1);
		}
		else
			cd_part2(data, av[0]);
	}
	return (0);
}
