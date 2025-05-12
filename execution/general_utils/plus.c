
#include "../../minishell.h"

void	*malloc_p(size_t size, t_trash *gc, t_shell *data)
{
	void	*ret;
	t_trash	*new;

	ret = ft_calloc(size, 1);
	if (ret == NULL)
	{
		putstr_fd("Malloc failed.\n", 2);
		stop_programm(data);
	}
	else
	{
		new = gc_new(ret, data);
		if (new == NULL)
		{
			free(ret);
			putstr_fd(GCAPPEND_ERRMSG, 2);
			stop_programm(data);
		}
		gc_add(&gc, new);
	}
	return (ret);
}
