/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_unit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:29:56 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/27 19:35:18 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_len(char *str, char *milestone)
{
	int	i;

	i = 0;
	while (&str[i] != milestone)
		i++;
	return (i);
}

void	cpy_remain(char **input, char **final, t_shell *data)
{
	int		len;
	char	*res;
	t_sub	info;

	len = ft_strlen(*input);
	info.len = len;
	info.start = 0;
	info.s = *input;
	res = ft_substr_s(&info, LOOP, data);
	*final = ft_strjoin(*final, res, LOOP, data);
	*input += len;
}

void	cpy_incr(char **input, char **tmp, char **final, t_shell *data)
{
	int		len;
	char	*res;
	t_sub	info;

	len = get_len(*input, *tmp);
	info.len = len;
	info.start = 0;
	info.s = *input;
	res = ft_substr_s(&info, LOOP, data);
	*final = ft_strjoin(*final, res, LOOP, data);
	*input += len;
}

int	extract_name(char **input, char **tmp, char **name, t_shell *data)
{
	int		name_len;
	t_sub	info;

	name_len = get_len(*input, *tmp);
	info.len = name_len;
	info.start = 0;
	info.s = *input;
	*name = ft_substr_s(&info, LOOP, data);
	*input += name_len;
	return (name_len);
}

void	join_remain(char **input, char **tmp, char **final, t_shell *data)
{
	if (*tmp)
		cpy_incr(input, tmp, final, data);
	else
		cpy_remain(input, final, data);
}
