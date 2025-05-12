
#include "../../minishell.h"

int	env(t_shell *data)
{
	t_list	*envl;

	envl = data->envl;
	while (envl)
	{
		if (envl->hide == 0)
			printf("%s\n", envl->s);
		envl = envl->next;
	}
	return (0);
}
