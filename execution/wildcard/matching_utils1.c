
#include "../../minishell.h"

static size_t	count_occurrences(char *str, char *sub)
{
	size_t	count;
	char	*tmp;

	count = 0;
	tmp = str;
	while (tmp != NULL)
	{
		tmp = ft_strnstr(tmp, sub, ft_strlen(tmp));
		if (tmp != NULL)
		{
			count++;
			tmp += ft_strlen(sub);
		}
	}
	return (count);
}

static void	replace_key_with_star(char *dest, char *src, char *key)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	while (*src)
	{
		if (ft_strncmp(src, key, key_len) == 0)
		{
			*dest = '*';
			dest++;
			src += key_len;
		}
		else
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	*dest = '\0';
}

char	*bring_star_back(char *input, char *key, t_shell *data)
{
	size_t	input_len;
	size_t	key_len;
	size_t	count;
	size_t	new_len;
	char	*result;

	if (input == NULL || key == NULL)
		return (NULL);
	input_len = ft_strlen(input);
	key_len = ft_strlen(key);
	count = count_occurrences(input, key);
	new_len = input_len - (count * (key_len - 1));
	result = which_malloc(LOOP, new_len + 1, data);
	replace_key_with_star(result, input, key);
	return (result);
}
