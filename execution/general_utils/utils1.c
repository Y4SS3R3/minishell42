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

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*final;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = -1;
	j = 0;
	final = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!final)
		return (NULL);
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
	free(to_free);
	return (NULL);
}

void	putstr_fd(char *msg, int fd)
{
	while (*msg)
	{
		write(fd, msg, 1);
		msg++;
	}
}

void	lst_free(t_token *head)
{
	while (head)
	{
		free(head);
		head = head->next;
	}
}

int	get_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
