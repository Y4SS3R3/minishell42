
#include "../../minishell.h"
#include <sys/wait.h>

void	redir_exec(t_token *root, t_shell *data)
{
	if (ft_strcmp(root->cmd, "<<"))
	{
		if (ft_expand(root, data) < 0)
		{
			putstr_fd("starshell: ambiguous redirect\n", 2);
			return ;
		}
	}
	if (root->before && handle_redirs(root->before, data, 0) == -1)
	{
		data->status = 1;
		return ;
	}
	if (root->after && handle_redirs(root->after, data, 0) == -1)
	{
		data->status = 1;
		return ;
	}
	data->status = 0;
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
	else if (is_a_redir(root))
		redir_exec(root, data);
	else
	{
		if (is_a_builtin(root))
			handle_builtin(root, data);
		else
		{
			waitpid(exec_child(root, data), &data->status, 0);
			update_status(data);
			tcsetattr(STDERR_FILENO, TCSANOW, &data->orig_termios);
		}
	}
}
