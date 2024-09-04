/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:12:47 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/04 17:26:46 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_values(int *len, char *input, int *i, t_shell *data)
{
	*len = ft_strlen(input);
	*i = -1;
	data->rem1 = -1;
	data->rem2 = -1;
}

static char	*rq_util1(int *i, char *input, t_shell *data)
{
	data->rem2 = *i;
	*i = *i - 2;
	return (remove_charindex(input, data->rem1, data->rem2, data));
}

static void	rq_util2(int *switch_f, int *len, char *input)
{
	*switch_f = 0;
	*len = ft_strlen(input);
}

static void	rq_util3(int *i, int *switch_f, char *input, t_shell *data)
{
	*switch_f = get_switch_value(input[*i]);
	data->rem1 = *i;
	(*i)++;
}

char	*remove_quotes(char *input, t_shell *data)
{
	int	len;
	int	i;
	int	switch_f;

	init_values(&len, input, &i, data);
	while (input && input[++i])
	{
		rq_util2(&switch_f, &len, input);
		if (input[i] == '"' || input[i] == '\'')
		{
			rq_util3(&i, &switch_f, input, data);
			while (input[i])
			{
				if (input[i] == switch_f)
				{
					input = rq_util1(&i, input, data);
					if (input == NULL)
						return (NULL);
					break ;
				}
				i++;
			}
		}
	}
	return (input);
}
