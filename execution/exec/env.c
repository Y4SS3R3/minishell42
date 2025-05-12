
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

	new_envp = which_malloc(GLOBAL, 5 * sizeof(char *), data);
	new_envp[0] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.",
			GLOBAL, data);
	new_envp[1] = ft_strdup("PWD=/Users/ymassiou", GLOBAL, data);
	new_envp[2] = ft_strdup("SHLVL=1", GLOBAL, data);
	new_envp[3] = ft_strdup("_=/usr/bin/env", GLOBAL, data);
	new_envp[4] = NULL;
	if (!new_envp[0] || !new_envp[1] || !new_envp[2] || !new_envp[3])
		return (NULL);
	return (new_envp);
}

void	check_env(t_shell *data)
{
	char	**env;

	env = data->envp;
	if (*env == NULL)
		data->envp = export_base_env(data);
}
