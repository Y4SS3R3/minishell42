
#include "../minishell.h"

static int	mz_is_ok(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	if (c == '\"' || c == '\'')
		return (1);
	if (c == '\0')
		return (1);
	if (c == '(' || c == ')' || c == '|')
		return (1);
	return (0);
}

static int	mz_swap_qt(char *s, int i, char c)
{
	while (i > 0 && mz_is_ok(s[i - 1]) == 0)
	{
		if (i > 1 && (s[i - 1] == '&' && s[i - 2] == '&'))
			break ;
		s[i] = s[i - 1];
		s[i - 1] = c;
		i--;
	}
	i++;
	while (s[i] != c)
		i++;
	while (s[i] && mz_is_ok(s[i + 1]) == 0)
	{
		if (s[i + 1] && (s[i + 1] == '&' && s[i + 2] == '&'))
			break ;
		s[i] = s[i + 1];
		s[i + 1] = c;
		i++;
	}
	return (i + 1);
}

char	*mz_joiner(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		flag = mz_flag(s[i], flag);
		if (flag != 0)
		{
			i = mz_swap_qt(s, i, s[i]);
			flag = 0;
		}
		else
			i++;
	}
	return (s);
}
