
#include "../minishell.h"

static unsigned int	mz_wrd_cnt(const char *s, char c)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			j++;
		while (s[i] != c && s[i])
			i++;
	}
	return (j);
}

static char	*mz_word_finder(const char *s, char c, int *word, t_shell *data)
{
	int		i;
	int		j;
	char	*str;

	while (s[*word] && s[*word] == c)
		(*word)++;
	i = *word;
	while (s[*word] && s[*word] != c)
		(*word)++;
	str = which_malloc(LOOP, (*word - i) + 1, data);
	j = 0;
	while (i + j < *word)
	{
		str[j] = s[j + i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	**mz_split(char const *s, char c, t_shell *data)
{
	char			**final;
	unsigned int	i;
	int				word;

	if (!s)
		return (NULL);
	word = 0;
	i = 0;
	final = which_malloc(LOOP, (mz_wrd_cnt(s, c) + 1) * sizeof(char *), data);
	while (i < mz_wrd_cnt(s, c))
	{
		final[i] = mz_word_finder(s, c, &word, data);
		i++;
		word++;
	}
	final[i] = NULL;
	return (final);
}
