/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:09:13 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/28 20:22:56 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_expand(t_token *node, t_shell *data)
{
	int	ret;

	ret = 0;
	ex_remove_quotes(node, data);
	ex_checkargs(node, data);
	ex_checkcmd(node, data);
	ret = ex_checkredirs(node, data);
	ret += ft_star(node, data);
	return (ret);
}
