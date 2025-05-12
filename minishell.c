
#include "minishell.h"

static int	repeat(t_shell *data)
{
	char	*line;

	data->exec = 1;
	data->unlink_it = 0;
	data->show_err = 0;
	data->free_it = 1;
	data->filcollect = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
	data->l_gc = init_l_gc(data);
	if (data->l_gc)
		init_path(data);
	data->fildes = ft_strdup(".", LOOP, data);
	line = prompt_user(data);
	if (prompt_manage(data, line))
		return (-1);
	data->fork = 0;
	close_fildes(data);
	if (data->free_it)
		free_command(data);
	free(line);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_shell	data;

	(void)av;
	if (ac != 1 || !isatty(0))
		return (1);
	rl_catch_signals = 0;
	data.l_gc = NULL;
	data.g_gc = init_shell(&data, env);
	init_shell_1(&data);
	while ('Y')
	{
		if (repeat(&data))
			break ;
	}
	if (data.free_it)
		free_programm(&data);
	return (0);
}
