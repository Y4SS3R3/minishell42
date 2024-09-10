/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 04:05:50 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/10 11:35:18 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_var(char *val, char *name, t_list *node, t_shell *data)
{
	char	*new;

	new = NULL;
	if (node == NULL)
	{
		append_to_env(name, val, 1, data);
		return ;
	}
	name = get_var_name(node->s, data);
	new = ft_strjoin(name, "=", GLOBAL, data);
	new = ft_strjoin(new, val, GLOBAL, data);
	node->s = new;
	node->hide = 0;
	data->envp = list_to_arr(data->envl, data);
}

static void	trim_string_util(char **start, char *str)
{
	*start = str;
	while (**start && **start == ' ')
		(*start)++;
}

char	*trim_string(char *str, t_shell *data)
{
	char	*start;
	size_t	len;
	char	*result;
	char	*end;

	trim_string_util(&start, str);
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
