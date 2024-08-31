/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:37:57 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/31 21:59:02 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_star(t_token *node, t_shell *data)
{
	star_checkargs(node, data);
	star_checkcmd(node, data);
	return (star_checkredirs(node, data));
}
