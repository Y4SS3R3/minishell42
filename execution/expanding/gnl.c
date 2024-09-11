/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:24:42 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/11 16:41:30 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*mz_dup_clean(char **ptr_to_final, t_shell *data)
{
	char	*s;

	s = mz_strdup(*ptr_to_final, data);
	*ptr_to_final = NULL;
	return (s);
}

static char	*mz_make(char **ptr_to_final, t_shell *data)
{
	char	*s;
	char	*tmp;
	int		nl_index;

	if (!*ptr_to_final)
		return (NULL);
	if (**ptr_to_final == '\0')
		return (*ptr_to_final = NULL, NULL);
	nl_index = mz_strchr(*ptr_to_final, '\n');
	if (nl_index == -1)
		return (mz_dup_clean(ptr_to_final, data));
	else
	{
		s = which_malloc(LOOP, nl_index + 2, data);
		mz_strlcpy(s, *ptr_to_final, nl_index + 2);
		tmp = *ptr_to_final;
		*ptr_to_final = mz_strdup(*ptr_to_final + nl_index + 1, data);
	}
	return (s);
}

static char	*mz_append(int fd, char *buffer, char **ptr_to_final, t_shell *data)
{
	ssize_t	n;
	char	*tmp;

	n = read(fd, buffer, 10);
	while (n > 0)
	{
		buffer[n] = '\0';
		tmp = *ptr_to_final;
		*ptr_to_final = mz_strjoin(tmp, buffer, data);
		tmp = NULL;
		if (mz_strchr(*ptr_to_final, '\n') != -1)
			break ;
		n = read(fd, buffer, 10);
	}
	if (n == -1)
	{
		*ptr_to_final = NULL;
		return (NULL);
	}
	return (mz_make(ptr_to_final, data));
}

char	*get_next_line(int fd, t_shell *data)
{
	static char	*final;
	char		*buffer;
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || 10 <= 0)
		return (NULL);
	buffer = which_malloc(LOOP, (size_t)10 + 1, data);
	line = mz_append(fd, buffer, &final, data);
	return (line);
}
