/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:28:22 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/11 14:21:51 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (len == 0 && haystack == NULL)
		return (NULL);
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < len && haystack[i + j])
			j++;
		if (needle[j] == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1, int mode, t_shell *data)
{
	size_t	size1;
	char	*tmp;

	tmp = NULL;
	size1 = ft_strlen(s1) + 1;
	tmp = which_malloc(mode, size1, data);
	return (ft_memcpy(tmp, s1, size1));
}

char	*ft_substr_s(t_sub *info, int mode, t_shell *data)
{
	size_t				i;
	char				*result;
	char				*s;
	unsigned int		start;
	size_t				len;

	s = info->s;
	start = info->start;
	len = info->len;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup("", mode, data));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	i = 0;
	result = which_malloc(mode, len + 1, data);
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[len] = 0;
	return (result);
}

char	*randomize_file_name(t_shell *data)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (i < OPEN_MAX)
	{
		name = ft_itoa(i, LOOP, data);
		name = ft_strjoin("/tmp/", name, LOOP, data);
		if (access(name, F_OK) == -1)
			return (name);
		i++;
	}
	return (NULL);
}
