/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:09:13 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/03 16:35:32 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ex_join(t_token *node, t_shell *data)
{
	int	size;

	if (node->join && node->cmd && node->args && node->args[0])
	{
		node->cmd = ft_strjoin(node->cmd, node->args[0], LOOP, data);
		size = get_length(node->args);
		node->args = ym_arr_rem(node->args, 0, &size, data);
	}
}

int	ft_expand(t_token *node, t_shell *data)
{
	int	ret;

	ret = 0;
	ex_remove_quotes(node, data);
	ex_join(node, data);
	ex_checkargs(node, data);
	ex_checkcmd(node, data);
	ret = ex_checkredirs(node, data);
	ret += ft_star(node, data);
	return (ret);
}
