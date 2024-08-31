/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:06:36 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 11:34:52 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*malloc_p(size_t size, t_trash *gc, t_shell *data)
{
	void	*ret;
	t_trash	*new;

	ret = ft_calloc(size, 1);
	if (ret == NULL)
	{
		data->free_it = 0;
		free_command(data, NULL);
		free_programm(data);
		exit(MALLOC_FAILURE);
	}
	else
	{
		new = gc_new(ret, data);
		if (!new)
		{
			data->free_it = 0;
			free_command(data, NULL);
			free_programm(data);
			exit(MALLOC_FAILURE);
		}
		gc_add(&gc, new);
	}
	return (ret);
}
