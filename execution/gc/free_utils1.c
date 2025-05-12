
#include "../../minishell.h"

void	free_programm(t_shell *data)
{
	if (!data->free_it)
		return ;
	gc_free(data, GLOBAL);
	free_trash(data->g_gc);
}

void	free_command(t_shell *data)
{
	if (!data->free_it)
		return ;
	gc_free(data, LOOP);
	free_trash(data->l_gc);
}
