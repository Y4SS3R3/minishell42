/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 04:05:50 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/09 17:42:19 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*trim_string(char *str, t_shell *data)
{
	char	*start;
	size_t	len;
	char	*result;
	char	*end;

	start = str;
	while (*start && *start == ' ')
		start++;
	if (*start == '\0')
	{
		result = which_malloc(LOOP, 1, data);
		if (result == NULL)
			return (NULL);
		if (result)
			*result = '\0';
		return (result);
	}
	end = str + ft_strlen(str) - 1;
	while (end > start && *end == ' ')
		end--;
	len = end - start + 1;
	result = which_malloc(LOOP, len + 1, data);
	if (result == NULL)
		return (NULL);
	ft_strncpy(result, start, len);
	result[len] = 0;
	return (result);
}
