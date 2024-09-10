/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:24:34 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:56:59 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(t_shell *data)
{
	char	*s;

	s = getcwd(NULL, 0);
	gc_add(&data->l_gc, gc_new(s, data));
	if (!s)
	{
		s = search_fetch_add(data->envp, "PWD", data);
		if (!s)
		{
			putstr_fd("pwd: error retrieving current directory:getcwd: ", 2);
			putstr_fd("cannot access parent directories\n", 2);
			return (1);
		}
		else
			printf("%s\n", get_var_value("PWD", data));
		return (0);
	}
	printf("%s\n", s);
	return (0);
}
