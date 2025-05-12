
#include "../minishell.h"

size_t	ft_strlen_mz(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_mz(const char *s1, t_shell *data)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = which_malloc(LOOP, ft_strlen_mz(s1) + 1, data);
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_substr_mz(char const *s, unsigned int start,
		size_t len, t_shell *data)
{
	size_t	tol;
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen_mz(s))
		return (ft_strdup_mz("", data));
	if (len > ft_strlen_mz(s) - start)
		tol = ft_strlen_mz(s) - start;
	else
		tol = len;
	sub = which_malloc(LOOP, tol + 1, data);
	while (i < tol)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin_mz(char const *s1, char const *s2, t_shell *data)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	z;
	char			*final;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_mz(s2, data));
	if (!s2)
		return (ft_strdup_mz(s1, data));
	i = -1;
	j = 0;
	z = ft_strlen_mz(s1);
	final = which_malloc(LOOP, z + ft_strlen_mz(s2) + 1, data);
	while (s1[++i])
		final[i] = s1[i];
	while (s2[j])
		final[i++] = s2[j++];
	final[i] = '\0';
	return (final);
}
