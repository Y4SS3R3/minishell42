
#include "../../minishell.h"

void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	check_for_quotes(char *str)
{
	int		len;
	char	first;
	char	last;

	len = ft_strlen(str);
	if (len < 2)
		return (0);
	first = str[0];
	last = str[len - 1];
	if ((first == '\'' && last == '\'') || (first == '"' && last == '"'))
		return (1);
	return (0);
}

void	generate_find_replace(char **to_find,
	char **replace_with, char *key, t_shell *data)
{
	*to_find = ft_strjoin(*to_find, key, LOOP, data);
	*to_find = ft_strjoin(*to_find, key, LOOP, data);
	*to_find = ft_strjoin(*to_find, data->key3, LOOP, data);
	*replace_with = ft_strjoin(*replace_with, key, LOOP, data);
	*replace_with = ft_strjoin(*replace_with, "*", LOOP, data);
	*replace_with = ft_strjoin(*replace_with, key, LOOP, data);
}

char	*star_check(char *input, t_shell *data)
{
	char	*to_find;
	char	*replace_with;

	to_find = NULL;
	replace_with = NULL;
	generate_find_replace(&to_find, &replace_with, data->key2, data);
	input = remove_quotes(input, data);
	input = find_replace(input, to_find, replace_with, data);
	to_find = NULL;
	replace_with = NULL;
	to_find = ft_strjoin(to_find, data->key, LOOP, data);
	to_find = ft_strjoin(to_find, data->key, LOOP, data);
	to_find = ft_strjoin(to_find, "*", LOOP, data);
	replace_with = ft_strjoin(replace_with, data->key, LOOP, data);
	replace_with = ft_strjoin(replace_with, "*", LOOP, data);
	replace_with = ft_strjoin(replace_with, data->key, LOOP, data);
	input = find_replace(input, to_find, replace_with, data);
	return (input);
}

void	ex_remove_quotes(t_token *node, t_shell *data)
{
	int		i;
	t_redir	*before;
	t_redir	*after;

	i = 0;
	node->cmd = star_check(node->cmd, data);
	before = node->before;
	after = node->after;
	while (node->args && node->args[i])
	{
		node->args[i] = star_check(node->args[i], data);
		i++;
	}
	while (before)
	{
		before->file = star_check(before->file, data);
		before = before->next;
	}
	while (after)
	{
		after->file = star_check(after->file, data);
		after = after->next;
	}
}
