/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:47:45 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/08 13:10:01 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_var_name(char *var, t_shell *data)
{
	char	*res;
	int		i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	res = which_malloc(GLOBAL, i + 1, data);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		res[i] = var[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

void	search_remove(t_list **haystack, char *needle, t_shell *data)
{
	t_list	*curr;
	char	*tmp;

	curr = *haystack;
	while (curr)
	{
		tmp = get_var_name(curr->s, data);
		if (tmp == NULL)
			break ;
		if (!ft_strcmp(tmp, needle))
		{
			remove_token(haystack, curr);
			break ;
		}
		curr = curr->next;
	}
}

int	export_var(int ac, char **av, t_shell *data)
{
	int		i;
	int		ret;
	int		tmp;
	char	*var_name;
	char	*var_value;

	i = 0;
	ret = 0;
	tmp = ret;
	var_name = NULL;
	var_value = NULL;
	while (i < ac)
	{
		tmp = parse_var(av[i], &var_value, &var_name, data);
		if (tmp != 0)
			ret = tmp;
		else
			append_to_env(var_name, var_value, 1, data);
		i++;
	}
	data->envp = list_to_arr(data->envl, data);
	return (ret);
}
