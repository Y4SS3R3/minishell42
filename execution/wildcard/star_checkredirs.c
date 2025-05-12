
#include "../../minishell.h"

int	star_check_before(t_token *node, t_shell *data)
{
	t_redir	*before;
	char	*file;
	char	*entry_content;

	before = node->before;
	while (before)
	{
		file = before->file;
		if (ft_strcmp(before->type, "<<"))
		{
			if (ft_strnstr(file, data->key3, ft_strlen(file)))
			{
				file = bring_star_back(file, data->key3, data);
				entry_content = get_entry_content(file, data);
				if (entry_content == NULL)
					return (-1);
				if (check_ambiguos(entry_content) == -1)
					return (-1);
				else
					node->before->file = remove_ws(entry_content, data);
			}
		}
		before = before->next;
	}
	return (0);
}

int	star_check_after(t_token *node, t_shell *data)
{
	t_redir	*after;
	char	*file;
	char	*entry_content;

	after = node->after;
	while (after)
	{
		file = after->file;
		if (ft_strcmp(after->type, "<<"))
		{
			if (ft_strnstr(file, data->key3, ft_strlen(file)))
			{
				file = bring_star_back(file, data->key3, data);
				entry_content = get_entry_content(file, data);
				if (entry_content == NULL)
					return (-1);
				if (check_ambiguos(entry_content) == -1)
					return (-1);
				else
					node->after->file = remove_ws(entry_content, data);
			}
		}
		after = after->next;
	}
	return (0);
}

int	star_checkredirs(t_token *node, t_shell *data)
{
	if (star_check_before(node, data))
		return (-1);
	if (star_check_after(node, data))
		return (-1);
	return (0);
}
