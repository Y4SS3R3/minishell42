/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:21:00 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/09 17:47:32 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_charindex(char *src, int i1, int i2, t_shell *data)
{
	int		len;
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	len = ft_strlen(src) - 1;
	ret = which_malloc(LOOP, len, data);
	if (!ret)
		return (NULL);
	if (data->errno_shell == MALLOC_FAILURE)
		return (NULL);
	while (src[i] && j < len)
	{
		if (i == i1 || i == i2)
			i++;
		else
		{
			ret[j] = src[i];
			j++;
			i++;
		}
	}
	ret[j] = 0;
	return (ret);
}

int	get_switch_value(int c)
{
	int	switch_f;

	if (c == '"')
		switch_f = '"';
	else
		switch_f = '\'';
	return (switch_f);
}
