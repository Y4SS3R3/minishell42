/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_hec_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:25:13 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/29 15:40:28 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ex_key_2_assign(char *s, char *key_s, t_shell *data)
{
	char	*res;
	t_info	info;

	info.final = malloc_p(ex_mz_size_count(s, key_s), data->l_gc, data);
	ex_mz_key_insert(&info, s, key_s);
	res = info.final;
	return (res);
}
