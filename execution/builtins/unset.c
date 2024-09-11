/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:26:23 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/11 14:26:25 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	unset_init(int *i, int *ret, char **name)
{
	*i = 0;
	*ret = 0;
	*name = NULL;
}

int	unset(int ac, char **av, t_shell *data)
{
	char	*name;
	int		i;
	int		ret;
	int		tmp;

	unset_init(&i, &ret, &name);
	if (ac == 0)
		return (0);
	else
	{
		while (i < ac)
		{
			tmp = check_var(av[i], &name, data);
			if (tmp)
				ret = tmp;
			if (tmp == -1)
				return (1);
			search_remove(&data->envl, name, data);
			i++;
		}
	}
	data->envp = list_to_arr(data->envl, data);
	return (ret);
}
