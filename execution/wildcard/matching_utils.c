/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matching_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:38:53 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/11 14:19:50 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_entry_content(char *pattern, t_shell *data)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*entry_content;

	dir = opendir(".");
	entry_content = NULL;
	if (dir == NULL)
		return (perror("Unable to open directory"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry && *entry->d_name != '.' && match_it(entry->d_name, pattern))
		{
			entry_content = ft_strjoin(entry_content,
					entry->d_name, LOOP, data);
			entry_content = ft_strjoin(entry_content, " ",
					LOOP, data);
		}
	}
	closedir(dir);
	return (entry_content);
}

char	*remove_ws(char *str, t_shell *data)
{
	int		i;
	int		len;
	int		j;
	char	*res;

	len = 0;
	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i + len] && !(str[i + len] == ' ' || str[i + len] == '\t'))
		len++;
	res = which_malloc(LOOP, len + 1, data);
	while (j < len)
	{
		res[j] = str[i + j];
		j++;
	}
	res[len] = '\0';
	return (res);
}

void	alpha_sort(char **arr, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) != 0
				|| (arr[j][0] >= 'a' && arr[j][0] <= 'z' &&
				arr[j + 1][0] >= 'A' && arr[j + 1][0] <= 'Z'))
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
