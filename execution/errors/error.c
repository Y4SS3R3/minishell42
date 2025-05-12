
#include "../../minishell.h"

void	unlink_fil(t_shell *data)
{
	int		i;
	int		j;
	char	*files;
	char	*file;

	i = 0;
	j = 0;
	files = data->filcollect;
	file = NULL;
	if (files == NULL)
		return ;
	while (files[i])
	{
		j = 0;
		while (files[i] && files[i] == '.')
			i++;
		j = i;
		while (files[j] && files[j] != '.')
			j++;
		file = ft_substr_mz(files, i, j, data);
		unlink(file);
		while (files[i] && files[i] != '.')
			i++;
	}
}

void	clean(t_shell *data)
{
	rl_clear_history();
	close_fildes(data);
	unlink_fil(data);
	free_command(data);
	free_programm(data);
}

void	stop_programm(t_shell *data)
{
	clean(data);
	exit(MALLOC_FAILURE);
}

void	fds_error(t_shell *data, char *msg)
{
	putstr_fd(msg, 2);
	data->status = 1;
	close_fildes(data);
}

void	improved_exit(int val, t_shell *data)
{
	clean(data);
	exit(val);
}
