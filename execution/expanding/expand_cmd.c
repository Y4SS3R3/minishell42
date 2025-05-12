
#include "../../minishell.h"

static char	**ex_getarg(char *str, char **command, t_shell *data)
{
	int		i;
	int		len;
	char	**args;

	i = 0;
	len = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && !(str[i] == ' ' || str[i] == '\t'))
	{
		i++;
		len++;
	}
	i = i - len;
	*command = ws_strdup(&str[i], len, data);
	while (str[i] == ' ' && str[i])
		i++;
	args = ws_split(&str[i], data);
	return (args);
}

static void	no_match_ignore_first(t_token *node, t_shell *data)
{
	int		size;

	size = get_length(node->args);
	if (node->args && node->args[0])
	{
		node->cmd = ft_strdup(node->args[0], LOOP, data);
		node->args = ym_arr_rem(node->args, 0, &size, data);
		ex_checkcmd(node, data);
	}
	else
		node->cmd = NULL;
}

static void	cmd_ascend_arg_to_cmd(char **tmp_s, t_token *node, t_shell *data)
{
	int		size;
	t_arr	info;

	size = 0;
	node->cmd = tmp_s[0];
	size = get_length(tmp_s);
	tmp_s = ym_arr_rem(tmp_s, 0, &size, data);
	info.index = get_length(node->args);
	info.new_arr = node->args;
	info.old_arr = tmp_s;
	size = get_length(node->args);
	size++;
	node->args = ym_arr_in(&info, &size, data);
}

static void	cmd_expand_split(char *cmd, char *key, t_token *node, t_shell *data)
{
	char	**tmp_s;
	char	*tmp;
	char	*res;

	tmp = NULL;
	tmp_s = NULL;
	res = NULL;
	tmp = ex_assign(cmd, key, data);
	tmp_s = ex_getarg(tmp, &res, data);
	if (ex_words_count(tmp) > 1)
		cmd_ascend_arg_to_cmd(tmp_s, node, data);
	if (!keep_quotes(tmp))
		node->cmd = res;
	else
		node->cmd = tmp;
	if (!ft_strcmp(node->cmd, ""))
		no_match_ignore_first(node, data);
	ex_checkargs(node, data);
}

void	ex_checkcmd(t_token *node, t_shell *data)
{
	char	*cmd;
	char	*key;
	char	*key2;

	key = data->key;
	key2 = data->key2;
	while (node->cmd
		&& (ft_strnstr(node->cmd, key, ft_strlen(node->cmd))
			|| ft_strnstr(node->cmd, key2, ft_strlen(node->cmd))))
	{
		cmd = node->cmd;
		if (ft_strnstr(cmd, key, ft_strlen(cmd)))
			node->cmd = ex_assign(cmd, key, data);
		if (ft_strnstr(cmd, key2, ft_strlen(cmd)))
			cmd_expand_split(cmd, data->key2, node, data);
	}
}
