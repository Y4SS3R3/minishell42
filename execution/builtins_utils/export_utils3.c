/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:59:54 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/31 17:23:23 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	invalid_char_util(char *input, int i, t_shell *data)
{
	if (!ft_isalnum(input[i]) && input[i] != '_'
		&& input[i] != '\\' && input[i] != '$' && input[i] == '+')
	{
		if (input[i + 1] == '=')
			data->exapp = 1;
		else
		{
			putstr_fd("starshell: export: not a valid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}

static int	check_bs(int check)
{
	if (check > 1)
	{
		putstr_fd("starshell: export: not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

static int	invalid_char(char *input, int *i, t_shell *data)
{
	int	len;
	int	check;

	len = 0;
	check = 0;
	while (input[*i] && input[*i] != '='
		&& input[*i] != '\'' && input[*i] != '\"')
	{
		if (invalid_char_util(input, *i, data))
			return (1);
		if (input[*i] == '\\')
		{
			check++;
			if (check_bs(check))
				return (1);
			(*i)++;
		}
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}

char	*export_get_val(char *input, int k, int len, t_shell *data)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = malloc_p(len + 1, data->l_gc, data);
	while (j < len)
	{
		if (input[k] == '\\')
			k++;
		tmp[j] = input[k];
		k++;
		j++;
	}
	tmp[j] = 0;
	return (tmp);
}

int	parse_var(char *input, char **val, char **name, t_shell *data)
{
	int	i;
	int	k;
	int	len;

	i = 0;
	i = skip_var_name(input);
	if (i == -1)
		return (1);
	k = i;
	len = invalid_char(input, &i, data);
	*name = export_get_name(len, k, input, data);
	if (export_parse_name(*name))
		return (1);
	while (input[i] && input[i] != '='
		&& !(input[i] != '\'' && input[i] != '\"'))
		i++;
	len = check_get_len(input, &i, val, data);
	if (len == -1)
		return (0);
	k = i - len;
	*val = export_get_val(input, k, len, data);
	return (0);
}
