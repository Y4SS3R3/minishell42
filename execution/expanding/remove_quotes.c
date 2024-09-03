/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:12:47 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/03 16:49:53 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*remove_charindex(char *src, int i1, int i2, t_shell *data)
{
	int		len;
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	len = ft_strlen(src) - 1;
	ret = which_malloc(LOOP,len , data);
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

char	*remove_quotes(char *input, t_shell *data, int rem1, int rem2)
{
	int	len;
	int	i;
	int	switch_f;

	len = ft_strlen(input);
	i = -1;
	while (input[++i])
	{
		switch_f = 0;
		len = ft_strlen(input);
		if (input[i] == '"' || input[i] == '\'')
		{
			switch_f = get_switch_value(input[i]);
			rem1 = i;
			i++;
			while (input[i])
			{
				if (input[i] == switch_f)
				{
					rem2 = i;
					input = remove_charindex(input, rem1, rem2, data);
					if (input == NULL)
						return (NULL);
					i = i - 2;
					break ;
				}
				i++;
			}
		}
	}
	return (input);
}
