/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:59:52 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/10 09:12:41 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(char *currpwd, t_shell *data)
{
	t_list	*ret;

	ret = search_fetch_list(data->envl, "PWD", data);
	update_var(currpwd, "PWD", ret, data);
	ret = search_fetch_list(data->envl, "OLDPWD", data);
	update_var(data->saved_path, "OLDPWD", ret, data);
}

char	*join_chdir(char *currpwd, char *path, t_shell *data)
{
	putstr_fd("cd: error retrieving current directory: ", 2);
	putstr_fd("getcwd: cannot access ", 2);
	putstr_fd("parent directories: No such file or directory\n", 2);
	currpwd = ft_strjoin(currpwd, path, LOOP, data);
	chdir(currpwd);
	return (currpwd);
}

void	cd_custompath(char *currpwd, char *path, t_shell *data)
{
	if (!ft_strcmp(path, "//"))
		currpwd = ft_strdup("//", GLOBAL, data);
	update_pwd(currpwd, data);
}
