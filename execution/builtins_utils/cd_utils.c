/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:31:33 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/10 08:24:46 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_var_value(char *name, t_shell *data)
{
	t_list	*node;
	char	*ret;
	char	*var;
	int		i;
	t_sub	info;

	i = 0;
	node = search_fetch_list(data->envl, name, data);
	if (node == NULL)
		return (NULL);
	var = node->s;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (ft_strdup("", GLOBAL, data));
	i++;
	info.len = ft_strlen(&var[i]);
	info.s = var;
	info.start = i;
	ret = ft_substr_s(&info, GLOBAL, data);
	return (ret);
}
