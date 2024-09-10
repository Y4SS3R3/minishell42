/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ym_arr_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:44:29 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/10 21:57:16 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**initialize_result(t_arr *info, int len1, int len2, t_shell *data)
{
	int		index;
	char	**result;

	index = info->index;
	if (index <= 0)
		index = 0;
	if (index > len1)
		index = len1;
	result = which_malloc(LOOP, (len1 + len2 + 1) * sizeof(char *), data);
	return (result);
}

static char	**append_to_host(t_arr *info, int len1, int len2, t_shell *data)
{
	int		i;
	int		j;
	char	**result;

	result = initialize_result(info, len1, len2, data);
	i = 0;
	while (i < info->index && info->old_arr && info->old_arr[i])
	{
		result[i] = ft_strdup(info->old_arr[i], LOOP, data);
		i++;
	}
	j = 0;
	while (j < len2 && info->new_arr[j])
	{
		result[i + j] = ft_strdup(info->new_arr[j], LOOP, data);
		j++;
	}
	while (i < len1 && info->old_arr[i])
	{
		result[i + len2] = ft_strdup(info->old_arr[i], LOOP, data);
		i++;
	}
	result[len1 + len2] = NULL;
	return (result);
}

static char	**no_host(char **new, t_shell *data)
{
	char	**result;
	int		len;
	int		i;

	len = get_length(new);
	result = which_malloc(LOOP, (len + 1) * sizeof(char *), data);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (new[i])
	{
		result[i] = ft_strdup(new[i], LOOP, data);
		i++;
	}
	result[i] = NULL;
	return (result);
}

static char	**no_new(char **host, t_shell *data)
{
	int		len;
	char	**result;
	int		i;

	i = 0;
	len = get_length(host);
	result = which_malloc(LOOP, (len + 1) * sizeof(char *), data);
	if (result == NULL)
		return (NULL);
	while (host[i])
	{
		result[i] = ft_strdup(host[i], LOOP, data);
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ym_arr_in(t_arr *info, int *size, t_shell *data)
{
	int		len1;
	int		len2;
	char	**result;
	char	**host;
	char	**new;

	host = info->old_arr;
	new = info->new_arr;
	if (host == NULL)
		return (no_host(new, data));
	if (new == NULL)
		return (no_new(host, data));
	if (host == NULL && new == NULL)
		return (NULL);
	len1 = get_length(host);
	len2 = get_length(new);
	result = append_to_host(info, len1, len2, data);
	*size = get_length(result);
	return (result);
}
