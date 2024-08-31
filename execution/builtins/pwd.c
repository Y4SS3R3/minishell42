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

	s = search_fetch_add(data->envp, "PWD", data);
	if (!s)
	{
		s = getcwd(NULL, 0);
		gc_add(&data->l_gc, gc_new(s, data));
		if (!s)
			putstr_fd("var not found!\n", 2);
		else
			printf("%s\n", s);
		return (0);
	}
	s = get_var("PWD", data);
	printf("%s\n", s);
	return (0);
}
