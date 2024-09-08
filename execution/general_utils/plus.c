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

static void	malloc_err(t_shell *data, int mode)
{
	data->free_it = 0;
	free_command(data, NULL);
	data->errno_shell = MALLOC_FAILURE;
	data->status = 1;
	if (mode == GLOBAL)
	{
		free_programm(data);
		exit(EXIT_FAILURE);
	}
}

void	*malloc_p(size_t size, t_trash *gc, t_shell *data, int mode)
{
	void	*ret;
	t_trash	*new;

	ret = ft_calloc(size, 1);
	dprintf(2, "Malloced : [%p]\n", ret);
	if (ret == NULL)
	{
		putstr_fd("Malloc failed.\n", 2);
		malloc_err(data, mode);
	}
	else
	{
		new = gc_new(ret, data);
		dprintf(2, "node of Malloced : [%p]\n", new);
		if (new == NULL)
		{
			putstr_fd("Warning: Appending newly allocated address failed.\n", 2);
			malloc_err(data, mode);
			return (NULL);
		}
		gc_add(&gc, new);
	}
	return (ret);
}
