
#include "../../minishell.h"

char	*mz_strjoin(char const *s1, char const *s2, t_shell *data)
{
	unsigned int	i;
	unsigned int	j;
	char			*final;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (mz_strdup(s2, data));
	if (!s2)
		return (mz_strdup(s1, data));
	i = -1;
	j = 0;
	final = which_malloc(LOOP, mz_strlen(s1) + mz_strlen(s2) + 1, data);
	while (s1[++i])
		final[i] = s1[i];
	while (s2[j])
		final[i++] = s2[j++];
	final[i] = '\0';
	return (final);
}

size_t	mz_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	mz_strchr(const char *s, char c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

size_t	mz_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = mz_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (i < dstsize -1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*mz_strdup(const char *s1, t_shell *data)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = which_malloc(LOOP, mz_strlen(s1) + 1, data);
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
