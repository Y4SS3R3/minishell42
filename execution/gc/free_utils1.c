/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:03:52 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/14 20:15:24 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_programm(t_shell *data)
{
	if (!data->free_it)
		return ;
	gc_free(data, GLOBAL);
	free_trash(data->g_gc);
}

void	free_command(t_shell *data)
{
	if (!data->free_it)
		return ;
	gc_free(data, LOOP);
	free_trash(data->l_gc);
}
