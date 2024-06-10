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

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(""));
	if (s2 == NULL)
		return (ft_strdup(s1));
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
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
