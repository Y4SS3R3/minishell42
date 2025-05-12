
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
		if (access(result, F_OK) != -1)
			return (result);
		i++;
	}
	return (command);
}

char	*check_command(char *command, char **paths, t_shell *data)
{
	if (command == NULL
		|| !ft_strcmp(command, ".")
		|| !ft_strcmp(command, "")
		|| !ft_strcmp(command, ".."))
		return (command);
	if (ft_strchr(command, '/') == NULL)
		return (create_path(paths, command, data));
	else
		return (command);
}
