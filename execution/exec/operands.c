/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:44:28 by ymassiou          #+#    #+#             */
/*   Updated: 2024/05/22 17:22:45 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


/*
problems when '|' is higher then '&&' / '||' in the tree 🤔
*/
void	and_handler(t_token *token, t_shell *data)
{
	int	pid1;
	int	pid2;

	pid1 = exec_child(token->left, data);
	waitpid(pid1, &data->status, 0);
	update_status(data);
	if (!data->status)
	{
		pid2 = exec_child(token->right, data);
		if (!data->index)
		{
			waitpid(pid2, &data->status, 0);
			update_status(data);
		}
	}
}

void	or_handler(t_token *token, t_shell *data)
{
	int	pid1;
	int	pid2;

	pid1 = exec_child(token->left, data);
	waitpid(pid1, &data->status, 0);
	update_status(data);
	if (data->status)
	{
		pid2 = exec_child(token->right, data);
		if (!data->index)
		{
			waitpid(pid2, &data->status, 0);
			update_status(data);
		}
	}
}

void	dfs_tree(t_token *root, t_shell *data)
{
	if (root == NULL)
		return ;
	if (root->nature == PIPE)
		pipe_line(root, data);
	else if (root->nature == AND)
		and_handler(root, data);
	else if (root->nature == OR)
		or_handler(root, data);
	else if (root->nature == WORD)
	{
		waitpid(exec_child(root, data), &data->status, 0);
		update_status(data);
	}
	else
		error_protocole("UNEXEPECTED IDENTIFIER !\n", data, EXIT_FAILURE);
}
