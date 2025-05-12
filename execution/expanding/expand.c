
#include "../../minishell.h"

static void	ex_join(t_token *node, t_shell *data)
{
	int	size;

	if (node->join && node->cmd && node->args && node->args[0])
	{
		node->cmd = ft_strjoin(node->cmd, node->args[0], LOOP, data);
		size = get_length(node->args);
		node->args = ym_arr_rem(node->args, 0, &size, data);
	}
}

static void	remove_dollar(t_token *node, t_shell *data)
{
	int	size;

	if (!node)
		return ;
	if (node->cmd
		&& !ft_strcmp(node->cmd, "$")
		&& node->args
		&& node->args[0]
		&& (**node->args == '"' || **node->args == '\''))
	{
		node->cmd = ft_strdup(node->args[0], LOOP, data);
		size = get_length(node->args);
		node->args = ym_arr_rem(node->args, 0, &size, data);
		node->join = 0;
	}
}

int	ft_expand(t_token *node, t_shell *data)
{
	int	ret;

	ret = 0;
	remove_dollar(node, data);
	ex_join(node, data);
	ex_remove_quotes(node, data);
	ex_checkargs(node, data);
	ex_checkcmd(node, data);
	ret = ex_checkredirs(node, data);
	ret += ft_star(node, data);
	return (ret);
}
