/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:04:41 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/31 21:32:55 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*prompt_user(t_shell *data)
{
	char	*rl;

	if (data->status == 0)
		rl = readline("\033[0m\033[0;32m✦\033[0m starshell: ");
	else
		rl = readline("\033[0;32m\033[0;31m✦\033[0m starshell: ");
	if (g_sig == SIGINT)
	{
		data->status = 1;
		g_sig = 0;
	}
	return (rl);
}

void	prompt_execution(t_shell *data, char *rl)
{
	t_token	*infix;
	int		key;

	add_history(rl);
	key = mz_key_assign(&rl);
	data->key = ft_itoa(key, LOOP, data);
	data->key2 = ft_itoa(key / 2, LOOP, data);
	infix = mz_parser(rl);
	if (infix != NULL)
	{
		data->fds = generate_heredoc(infix, data);
		if (data->exec)
		{
			assign_hdc(data->fds, infix);
			data->the_tree = NULL;
			data->the_tree = ft_tree(&infix, data);
			dfs_tree(data->the_tree, data);
		}
	}
	free_token(infix);
}

int	prompt_manage(t_shell *data, char *rl)
{
	if (!rl)
	{
		ctrl_d(data);
		return (1);
	}
	if (rl && *rl)
		prompt_execution(data, rl);
	else
		data->status = 0;
	return (0);
}
