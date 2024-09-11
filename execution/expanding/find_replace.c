/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:02:17 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/11 14:16:41 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	count_occurrences(char *s1, char *s2)
{
	char		*tmp;
	size_t		count;
	size_t		len_s2;
	char		*found;

	count = 0;
	tmp = s1;
	len_s2 = ft_strlen(s2);
	found = ft_strnstr(tmp, s2, ft_strlen(tmp));
	while (found)
	{
		count++;
		tmp = found + len_s2;
		found = ft_strnstr(tmp, s2, ft_strlen(tmp));
	}
	return (count);
}

static size_t	calculate_new_length(char *s1, char *s2, char *s3)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_s3;
	size_t	count;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_s3 = ft_strlen(s3);
	count = count_occurrences(s1, s2);
	return (len_s1 + count * (len_s3 - len_s2));
}

static void	init_lengths(size_t *len_s2, size_t *len_s3, char *s2, char *s3)
{
	*len_s2 = ft_strlen(s2);
	*len_s3 = ft_strlen(s3);
}

static char	*copy_and_replace(char *s1, char *s2, char *s3, char *result)
{
	char		*p;
	char		*current_pos;
	size_t		len;
	size_t		len_s2;
	size_t		len_s3;

	current_pos = result;
	init_lengths(&len_s2, &len_s3, s2, s3);
	while (*s1)
	{
		p = ft_strnstr(s1, s2, ft_strlen(s1));
		if (p)
		{
			len = p - s1;
			ft_memcpy(current_pos, s1, len);
			current_pos += len;
			ft_memcpy(current_pos, s3, len_s3);
			current_pos += len_s3;
			s1 = p + len_s2;
		}
		else
			break ;
	}
	ft_strcpy(current_pos, s1);
	return (result);
}

char	*find_replace(char *s1, char *s2, char *s3, t_shell *data)
{
	char	*result;
	size_t	new_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	new_len = calculate_new_length(s1, s2, s3);
	result = which_malloc(LOOP, new_len + 1, data);
	return (copy_and_replace(s1, s2, s3, result));
}
