
#include "../../minishell.h"

int	ex_words_count(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != '\t')
			&& (s[i + 1] == 0 || s[i + 1] == ' ' || s[i + 1] == '\t'))
			count++;
		i++;
	}
	return (count);
}

int	check_ambiguos(char *file)
{
	int	count;

	count = ex_words_count(file);
	if (count != 1)
		return (-1);
	return (0);
}

char	*ws_strdup(char *src, int len, t_shell *data)
{
	int		i;
	char	*res;

	i = 0;
	res = which_malloc(LOOP, len + 1, data);
	while (src[i] && !(src[i] == ' ' || src[i] == '\t'))
	{
		res[i] = src[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

int	keep_quotes(char *str)
{
	int	j;

	j = 0;
	if (ex_words_count(str) < 2)
		return (0);
	while (str[j])
		j++;
	if ((str[0] == '\'' || str[0] == '"')
		&& (str[j - 1] == '\'' || str[j - 1] == '"'))
		return (1);
	return (0);
}
