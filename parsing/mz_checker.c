
#include "../minishell.h"

int	mz_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	mz_is_special(char c)
{
	if (c == '\'' || c == '\"' || c == '|' || c == '<' || c == '>'
		|| c == '(' || c == ')' || c == '&')
		return (1);
	return (0);
}
