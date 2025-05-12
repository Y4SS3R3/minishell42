
#include "../../minishell.h"

int	export(int ac, char **av, t_shell *data)
{
	if (ac == 0)
		print_export(data->envl);
	else
		return (export_var(ac, av, data));
	return (0);
}
