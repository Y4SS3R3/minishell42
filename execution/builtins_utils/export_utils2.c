/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:48:06 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/09 17:38:30 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	invalid_1(char *input, int i)
{
	if (!ft_isalpha(input[i])
		&& input[i] != '_' && input[i] != '\\' && input[i] != '$')
	{
		putstr_fd("starshell: export: not a valid identifier\n", 2);
		return (-1);
	}
	return (0);
}

int	skip_var_name(char *input)
{
	int	i;
	int	ret;

	i = 0;
	while (input[i] && input[i] != '='
		&& !(input[i] != '\'' && input[i] != '\"'))
		i++;
	ret = invalid_1(input, i);
	if (ret)
		return (ret);
	return (i);
}

char	*export_get_name(int len, int k, char *input, t_shell *data)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = which_malloc(GLOBAL, len + 1, data);
	if (tmp == NULL)
		return (NULL);
	if (data->errno_shell == MALLOC_FAILURE)
		return (NULL);
	while (j < len)
	{
		if (input[k] == '\\')
		{
			k++;
			if (j < len)
				tmp[j] = input[k];
		}
		else
			tmp[j] = input[k];
		k++;
		j++;
	}
	tmp[j] = 0;
	return (tmp);
}

int	export_parse_name(char *tmp)
{
	int	j;

	j = 0;
	while (tmp[j])
	{
		if (!ft_isalnum(tmp[j]) && tmp[j] != '_' && tmp[j] != '+')
		{
			putstr_fd("starshell: export: not a valid identifier\n", 2);
			return (1);
		}
		j++;
	}
	return (0);
}

int	check_get_len(char *input, int *i, char **val, t_shell *data)
{
	int	len;

	len = 0;
	if (!input[*i])
	{
		data->add_equal = 0;
		return (-1);
	}
	(*i)++;
	if (!input[*i])
	{
		*val = "";
		return (-1);
	}
	while (input[*i])
	{
		(*i)++;
		len++;
	}
	return (len);
}
