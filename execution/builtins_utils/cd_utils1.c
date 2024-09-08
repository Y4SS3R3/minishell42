/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:59:52 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/08 11:07:01 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_chdir(char *currpwd, char *path, t_shell *data)
{
	putstr_fd("cd: error retrieving current directory: ", 2);
	putstr_fd("getcwd: cannot access ", 2);
	putstr_fd("parent directories: No such file or directory\n", 2);
	currpwd = ft_strjoin(currpwd, path, LOOP, data);
	chdir(currpwd);
	return (currpwd);
}

void	cd_custompath(char *path, char *oldpwd, t_shell *data)
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
	}
	if (oldpwd == NULL)
		oldpwd = get_var_value("OLDPWD", data);
	if (!ft_strcmp(path, "//"))
		currpwd = ft_strdup("//", GLOBAL, data);
	update_pwd(currpwd, data);
}
