
#include "../../minishell.h"

void	and_handler(t_token *token, t_shell *data)
{
	int	pid1;
	int	pid2;

	if (is_a_builtin(token->left))
		handle_builtin(token->left, data);
	else
	{
		pid1 = exec_child(token->left, data);
		waitpid(pid1, &data->status, 0);
		update_status(data);
	}
	if (!data->status)
	{
		if (is_a_builtin(token->right))
			handle_builtin(token->right, data);
		else
		{
			pid2 = exec_child(token->right, data);
			waitpid(pid2, &data->status, 0);
			update_status(data);
		}
	}
}

void	or_handler(t_token *token, t_shell *data)
{
	int	pid1;
	int	pid2;

	if (is_a_builtin(token->left))
		handle_builtin(token->left, data);
	else
	{
		pid1 = exec_child(token->left, data);
		waitpid(pid1, &data->status, 0);
		update_status(data);
	}
	if (data->status)
	{
		if (is_a_builtin(token->right))
			handle_builtin(token->right, data);
		else
		{
			pid2 = exec_child(token->right, data);
			waitpid(pid2, &data->status, 0);
			update_status(data);
		}
	}
}
