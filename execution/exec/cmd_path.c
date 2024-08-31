/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:28:00 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 10:24:57 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*create_path(char **paths, char *command, t_shell *data)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		result = ft_strjoin("/", command, GLOBAL, data);
		result = ft_strjoin(paths[i], result, GLOBAL, data);
		if (result == NULL)
			return (NULL);
		if (access(result, X_OK) != -1)
			return (result);
		i++;
	}
	return (NULL);
}

char	*check_command(char *command, char **paths, t_shell *data)
{
	char	*result;

	if (command == NULL)
		return (NULL);
	result = NULL;
	if (ft_strchr(command, '/') == NULL)
		return (create_path(paths, command, data));
	else
	{
		if (access(command, X_OK) == -1)
			return (NULL);
		else
			result = command;
	}
	return (result);
}
