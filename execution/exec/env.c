/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:33:20 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 11:40:30 by ymassiou         ###   ########.fr       */
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
		data->paths = NULL;
	data->paths = ft_split(res, ':', GLOBAL, data);
}

static char	**export_base_env(t_shell *data)
{
	char	**new_envp;

	new_envp = malloc_p(5 * sizeof(char *), data->g_gc, data);
	if (new_envp == NULL)
	{
		putstr_fd("ERROR IN MALLOC[014]!\n", 2);
		exit(EXIT_FAILURE);
	}
	new_envp[0] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.",
			GLOBAL, data);
	new_envp[1] = ft_strdup("PWD=/Users/ymassiou", GLOBAL, data);
	new_envp[2] = ft_strdup("SHLVL=1", GLOBAL, data);
	new_envp[3] = ft_strdup("_=/usr/bin/env", GLOBAL, data);
	new_envp[4] = NULL;
	return (new_envp);
}

void	check_env(t_shell *data)
{
	char	**env;

	env = data->envp;
	if (*env == NULL)
		data->envp = export_base_env(data);
}
