/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:33:20 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 10:24:21 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env(char **env)
{
	while (*env)
	{
		if (ft_strnstr(*env, "PATH", 5) != NULL)
			return (*env);
		env++;
	}
	return (NULL);
}

static char	*extract_path(char **env)
{
	char	*str;

	str = get_env(env);
	if (str == NULL)
		return (NULL);
	while (*str != '=')
		str++;
	return (str + 1);
}

void	check_potential_path(t_shell *data)
{
	char	*res;

	res = extract_path(data->envp);
	if (res == NULL)
		error_protocole("PATH variable not found\n", data, 127);
	data->paths = ft_split(res, ':');
}

void	check_env(t_shell *data, char **env)
{
	if (*env == NULL)
		error_protocole("Error in environment\n", data, 127);
	data->envp = env;
}
