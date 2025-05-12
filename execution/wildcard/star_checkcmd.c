
#include "../../minishell.h"

static void	insert_matched_stuff(char *entry_content,
	int *size, t_token *node, t_shell *data)
{
	char	**tmps;
	t_arr	info;

	tmps = ft_split(entry_content, ' ', LOOP, data);
	alpha_sort(tmps, get_length(tmps));
	if (tmps)
		node->cmd = ft_strdup(tmps[0], LOOP, data);
	tmps = ym_arr_rem(tmps, 0, size, data);
	info.old_arr = node->args;
	info.new_arr = tmps;
	info.index = 0;
	node->args = ym_arr_in(&info, size, data);
}

void	star_checkcmd(t_token *node, t_shell *data)
{
	char	*cmd;
	char	*entry_content;
	int		size;

	cmd = node->cmd;
	entry_content = NULL;
	if (cmd)
	{
		cmd = node->cmd;
		if (ft_strnstr(node->cmd, data->key3, ft_strlen(node->cmd)))
		{
			node->cmd = bring_star_back(node->cmd, data->key3, data);
			entry_content = get_entry_content(node->cmd, data);
			if (!entry_content)
				return ;
			size = get_length(node->args);
			if (entry_content)
				insert_matched_stuff(entry_content, &size, node, data);
		}
	}
}
