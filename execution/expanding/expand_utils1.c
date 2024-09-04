/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:43:32 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/04 16:14:21 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	expand(t_token *root, t_shell *data)
{
	int	ret;

	ret = ft_expand(root, data);
	if (ret != 0)
	{
		putstr_fd("starshell: ambiguous redirect\n", 2);
		data->status = 1;
		return (-1);
	}
	return (0);
}
