/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:59:52 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/09 21:19:20 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <errno.h>
#include <string.h>

char	*join_chdir(char *currpwd, char *path, t_shell *data)
{
	putstr_fd("cd: error retrieving current directory: ", 2);
	putstr_fd("getcwd: cannot access ", 2);
	putstr_fd("parent directories: No such file or directory\n", 2);
	currpwd = ft_strjoin(currpwd, path, LOOP, data);
	dprintf(2, "To chdir Path : [%s]\n", currpwd);
	if (chdir(currpwd) == -1)
	{
		putstr_fd("Chdir() call failure\n", 2);
		fprintf(stderr, "Error: %s\n", strerror(errno));
	}
	return (currpwd);
}

void	cd_custompath(char *path, t_shell *data)
{
	char	*currpwd;

	currpwd = getcwd(NULL, 0);
	gc_add(&data->l_gc, gc_new(currpwd, data));
	if (!ft_strcmp(path, "//"))
		currpwd = ft_strdup("//", GLOBAL, data);
	update_pwd(currpwd, data);
}
