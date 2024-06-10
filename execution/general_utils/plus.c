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

void	error_protocole(char *msg, t_shell *data, int exit_s)
{
	putstr_fd(msg, 2);
	// gc_free(data);
	// exit(exit_s);
}

void	*malloc_plus(size_t size, t_shell *data)
{
	void	*ret;
	t_trash	*new;

	ret = ft_calloc(size, 1);
	if (ret)
	{
		new = gc_new(ret);
		// if (!new)
		// 	gc_free(data);
		gc_add(&data->gc, new);
	}
	return (ret);
}

void	dup2_plus(int old, int new, t_shell *data)
{
	int	ret;

	ret = dup2(old, new);
	if (ret == -1)
		error_protocole("DUP2() ERROR[01]\n", data, EXIT_FAILURE);
	if (close (old) == -1)
		putstr_fd("LOL",2);
}
