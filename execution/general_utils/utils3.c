
#include "../../minishell.h"

static int	nbrlen(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*allocate(int len, int mode, t_shell *data)
{
	char	*allocated;

	allocated = which_malloc(mode, len + 1, data);
	return (allocated);
}

char	*ft_itoa(int n, int mode, t_shell *data)
{
	int		len;
	long	ntmp;
	char	*result;
	int		i;

	ntmp = n;
	i = 0;
	len = nbrlen(ntmp);
	result = allocate(len, mode, data);
	if (ntmp < 0)
	{
		result[i] = '-';
		i++;
		ntmp = -ntmp;
	}
	result[len--] = 0;
	while (len >= i)
	{
		result[len--] = (ntmp % 10) + 48;
		ntmp /= 10;
	}
	return (result);
}

static char	*gen_word(char *s, char c, t_shell *data)
{
	size_t	i;
	char	*result;
	t_sub	info;

	result = NULL;
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	info.s = s;
	info.start = 0;
	info.len = i;
	result = ft_substr_s(&info, GLOBAL, data);
	return (result);
}

char	**ft_split(char *s, char c, int mode, t_shell *data)
{
	size_t	words;
	char	**result;
	size_t	j;

	if (s == NULL)
		return (NULL);
	words = words_count(s, c);
	result = NULL;
	j = 0;
	result = which_malloc(mode, (words + 1) * sizeof(char *), data);
	while (*s && words--)
	{
		while (*s == c && *s)
			s++;
		result[j] = gen_word(s, c, data);
		if (result[j] == NULL)
			return (ft_free(result, j, 0));
		j++;
		while (*s != c && *s)
			s++;
	}
	result[j] = 0;
	return (result);
}
