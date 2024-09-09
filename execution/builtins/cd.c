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

void update_pwd(char *currpwd, t_shell *data)
{
	t_list *ret;

	ret = search_fetch_list(data->envl, "PWD", data);
	update_var(currpwd, "PWD",ret, data);
	ret = search_fetch_list(data->envl, "OLDPWD", data);
	update_var(data->saved_path, "OLDPWD", ret, data);
}

int	cd_home(char *oldpwd, t_shell *data)
{
	char	*home;
	char	*currpwd;

	home = search_fetch_add(data->envp, "HOME", data);
	if (home == NULL)
	{
		putstr_fd("bash: cd: HOME not set\n", 2);
		return (1);
	}
	else
	{
		if (chdir(home + 5))
		{
			perror(NULL);
			return (1);
		}
		else
		{
			currpwd = getcwd(NULL, 0);
			gc_add(&data->l_gc, gc_new(currpwd, data));
			if (currpwd == NULL)
			{
				puts("PWD IS NULL 1");
				currpwd = get_var_value("PWD", data);
			}
			if (oldpwd == NULL)
			{
				puts("OLDPWD IS NULL 1");
				oldpwd = get_var_value("OLDPWD", data);
			}
			update_pwd(currpwd, data);
		}
	}
	return (0);
}

int	cd(int ac, char **av, t_shell *data)
{
	// printf("%s\n", getcwd(NULL, 0));
	char *tmp;
	// char *path_to;
	char *oldpwd;
	char *currpwd;

	oldpwd = getcwd(NULL, 0);
	gc_add(&data->l_gc, gc_new(oldpwd, data));
	tmp = get_var_value("PWD", data);
	if (tmp)
		data->saved_path = tmp;
	if(ac == 0)
		return (cd_home(oldpwd, data));
	else
	{
		if (!ft_strcmp(av[0], "~"))
			return (cd_home(oldpwd, data));
		if (chdir(av[0]) != 0)
		{
			perror(av[0]);
			return (1);
		}
		else
		{
			currpwd = getcwd(NULL, 0);
			gc_add(&data->l_gc, gc_new(currpwd, data));
			if (currpwd == NULL)
			{
				currpwd = get_var_value("PWD", data);
				if (!ft_strcmp(av[0], ".."))
				{
					putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
					currpwd = ft_strjoin(currpwd, "/..", LOOP, data);
					chdir(currpwd);
				}
				if (!ft_strcmp(av[0], "."))
				{
					putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
					currpwd = ft_strjoin(currpwd, "/.", LOOP, data);
					chdir(currpwd);
				}
			}
			if (oldpwd == NULL)
				oldpwd = get_var_value("OLDPWD", data);
			if (!ft_strcmp(av[0], "//"))
				currpwd = ft_strdup("//", GLOBAL, data);
			update_pwd(currpwd, data);
		}
	}
	// printf("%s\n", getcwd(NULL, 0));
	return (0);
}
