/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:40:54 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/28 20:02:10 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	key_exist_check(char *str, t_shell *data)
{
	if (str
		&& (ft_strnstr(str, data->key, ft_strlen(str))
			|| ft_strnstr(str, data->key2, ft_strlen(str))))
		return (1);
	return (0);
}

static void	ex_insert_new_args(t_attrr *key_index,
			int *size, t_shell *data, t_token *node)
{
	char	*tmp;
	char	**tmps;
	t_arr	info;

	if (ft_strnstr(node->args[key_index->index],
			key_index->key2, ft_strlen(node->args[key_index->index])))
	{
		tmp = ex_assign(node->args[key_index->index], key_index->key2, data);
		if (!ft_strcmp(node->cmd, "export"))
			node->args[key_index->index] = tmp;
		else
		{
			tmps = ws_split(tmp, data);
			node->args = ym_arr_rem(node->args, key_index->index, size, data);
			info.index = key_index->index;
			info.new_arr = tmps;
			info.old_arr = node->args;
			node->args = ym_arr_in(&info, size, data);
		}
	}
	else if (ft_strnstr(node->args[key_index->index],
			key_index->key, ft_strlen(node->args[key_index->index])))
		node->args[key_index->index] = ex_assign(node->args[key_index->index],
				key_index->key, data);
}

void	ex_checkargs(t_token *node, t_shell *data)
{
	int		i;
	int		size;
	char	**tmps;
	t_attrr	key_index;

	i = 0;
	tmps = NULL;
	size = get_length(node->args);
	if (node->args)
	{
		while (i < size && node->args[i])
		{
			while (key_exist_check(node->args[i], data))
			{
				key_index.index = i;
				key_index.key = data->key;
				key_index.key2 = data->key2;
				ex_insert_new_args(&key_index, &size, data, node);
			}
			i++;
		}
	}
}
