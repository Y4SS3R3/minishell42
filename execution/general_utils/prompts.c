/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:04:41 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/05 17:20:53 by ymassiou         ###   ########.fr       */
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

static void	check_syntaxe_err(int status, t_token *infix, t_shell *data)
{
	if (status)
		data->status = status;
	else
	{
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
	}
}

static void	prompt_execution(t_shell *data, char *rl)
{
	t_token	*infix;
	int		key;
	int		status;

	status = 0;
	add_history(rl);
	key = mz_key_assign(&rl);
	data->key = ft_itoa(key, LOOP, data);
	data->key2 = ft_itoa(key / 2, LOOP, data);
	data->key3 = ft_itoa(key / 3, LOOP, data);
	rl = mz_key_assign2(rl, data->key3);
	infix = mz_parser(rl, &status);
	check_syntaxe_err(status, infix, data);
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
