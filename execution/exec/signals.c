/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:39:24 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/30 19:29:22 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ctrl_c(int sig)
{
	printf("\n");
	g_sig = sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_c_heredoc(int sig)
{
	close(0);
	g_sig = sig;
}

void	ctrl_d(t_shell *data)
{
	exit_cmd(0, NULL, data);
	gc_free(data, LOOP);
	free_trash(data->l_gc);
}
