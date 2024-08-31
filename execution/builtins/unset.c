/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:51:37 by marvin            #+#    #+#             */
/*   Updated: 2024/08/31 19:43:01 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset(int ac, char **av, t_shell *data)
{
	char	*name;
	int		i;
	int		ret;
	int		tmp;

	i = 0;
	ret = 0;
	name = NULL;
	if (ac == 0)
		return (0);
	else
	{
		while (i < ac)
		{
			tmp = check_var(av[i], &name, data);
			if (tmp)
				ret = tmp;
			search_remove(&data->envl, name, data);
			i++;
		}
	}
	data->envp = list_to_arr(data->envl, data);
	return (ret);
}
