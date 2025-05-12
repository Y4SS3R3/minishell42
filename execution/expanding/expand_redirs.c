
#include "../../minishell.h"

int	check_empty_str(char *file, t_shell *data)
{
	if (!ft_strcmp(file, ""))
	{
		putstr_fd("starshell: : No such file or directory\n", 2);
		data->status = 1;
		data->show_err = 1;
		return (-2);
	}
	return (0);
}

int	ex_before_redirs(t_token *node, t_shell *data)
{
	t_redir	*before;
	char	*file;

	before = node->before;
	while (before)
	{
		file = before->file;
		if (ft_strcmp(before->type, "<<"))
		{
			if (ft_strnstr(file, data->key, ft_strlen(file)))
				node->before->file = ex_assign(file, data->key, data);
			if (ft_strnstr(file, data->key2, ft_strlen(file)))
			{
				node->before->file = ex_assign(file, data->key2, data);
				if (check_ambiguos(node->before->file) == -1)
					return (-1);
			}
		}
		before = before->next;
	}
	return (0);
}

int	ex_after_redirs(t_token *node, t_shell *data)
{
	t_redir	*after;
	char	*file;
	int		expanded;

	after = node->after;
	while (after)
	{
		init_1(&file, &expanded, after->file);
		if (ft_strnstr(file, data->key, ft_strlen(file)))
		{
			node->after->file = ex_assign(file, data->key, data);
			expanded = 1;
		}
		if (ft_strnstr(file, data->key2, ft_strlen(file)))
		{
			node->after->file = ex_assign(file, data->key2, data);
			expanded = 1;
			if (check_ambiguos(node->after->file) == -1)
				return (-1);
		}
		if (expanded && check_empty_str(node->after->file, data))
			return (-2);
		after = after->next;
	}
	return (0);
}

int	ex_checkredirs(t_token *node, t_shell *data)
{
	int	ret;

	ret = ex_before_redirs(node, data);
	if (ret)
		return (ret);
	return (ex_after_redirs(node, data));
}
