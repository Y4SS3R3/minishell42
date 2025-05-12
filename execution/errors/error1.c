
#include "../../minishell.h"

void	exec_err1(char *str, t_shell *data)
{
	if (str && ft_strchr(str, '/'))
		check_ifdir(str, data);
	exec_err(str);
}
