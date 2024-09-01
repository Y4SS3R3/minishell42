/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_checkargs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 01:25:12 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/01 04:11:31 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	insert_matched_args(t_token *node,
	t_attrr *attrr, int *size, t_shell *data)
{
	char	**tmps;
	t_arr	info;

	node->args = ym_arr_rem(node->args, attrr->index, size, data);
	tmps = ft_split(attrr->key, ' ', LOOP, data);
	alpha_sort(tmps, get_length(tmps));
	info.index = attrr->index;
	info.new_arr = tmps;
	info.old_arr = node->args;
	node->args = ym_arr_in(&info, size, data);
}

static int	match_args(t_token *node, int i, int *size, t_shell *data)
{
	char	*entry_content;
	t_attrr	info;

	entry_content = NULL;
	entry_content = get_entry_content(node->args[i], data);
	if (!entry_content)
		return (-1);
	if (entry_content)
	{
		info.index = i;
		info.key = entry_content;
		info.key2 = NULL;
		insert_matched_args(node, &info, size, data);
	}
	return (0);
}

void	star_checkargs(t_token *node, t_shell *data)
{
	int		i;
	int		size;

	i = 0;
	size = get_length(node->args);
	if (node->args)
	{
		while (i < size)
		{
			if (ft_strnstr(node->args[i], data->key3,
					ft_strlen(node->args[i])))
			{
				node->args[i] = bring_star_back(node->args[i],
						data->key3, data);
				if (match_args(node, i, &size, data))
					return ;
			}
			i++;
		}
	}
}
