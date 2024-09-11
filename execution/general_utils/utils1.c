/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:05:18 by ymassiou          #+#    #+#             */
/*   Updated: 2024/05/05 20:01:08 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*which_malloc(int mode, size_t size, t_shell *data)
{
	void	*buffer;

	if (mode == GLOBAL)
		buffer = malloc_p(size, data->g_gc, data);
	else if (mode == LOOP)
		buffer = malloc_p(size, data->l_gc, data);
	else
		buffer = malloc(size);
	return (buffer);
}

char	*ft_strjoin(char const *s1, char const *s2, int mode, t_shell *data)
{
	unsigned int	i;
	unsigned int	j;
	char			*final;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2, mode, data));
	if (!s2)
		return (ft_strdup(s1, mode, data));
	i = -1;
	j = 0;
	final = which_malloc(mode, ft_strlen(s1) + ft_strlen(s2) + 1, data);
	while (s1[++i])
		final[i] = s1[i];
	while (s2[j])
		final[i++] = s2[j++];
	final[i] = '\0';
	return (final);
}

void	*ft_free(char **to_free, size_t elements, int flag)
{
	size_t	i;

	i = flag;
	if (!elements)
		return (NULL);
	if (i == 1)
	{
		while (to_free[i] != NULL)
		{
			free(to_free[i]);
			i++;
		}
	}
	else
	{
		while (i < elements)
		{
			free(to_free[i]);
			i++;
		}
	}
	return (NULL);
}

void	putstr_fd(char *msg, int fd)
{
	if (!msg)
		return ;
	while (*msg)
	{
		write(fd, msg, 1);
		msg++;
	}
}

int	get_length(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (i);
	while (array[i])
		i++;
	return (i);
}
