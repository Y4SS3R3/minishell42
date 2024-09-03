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

int	cd(int ac, char **av, t_shell *data)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	gc_add(&data->l_gc, gc_new(oldpwd, data));
	if (ac == 0)
		return (cd_home(data));
	else
	{
		if (!ft_strcmp(av[0], "~"))
			return (cd_home(data));
		if (chdir(av[0]) != 0)
		{
			perror(av[0]);
			return (1);
		}
		else
			cd_custompath(av[0], oldpwd, data);
	}
	return (0);
}
