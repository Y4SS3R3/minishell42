
#include "../../minishell.h"

void	close_fildes(t_shell *data)
{
	char	*fildes;
	int		i;
	int		to_close;

	fildes = data->fildes;
	i = 0;
	if (fildes == NULL)
		return ;
	while (fildes[i])
	{
		while (fildes[i] && fildes[i] == '.')
			i++;
		if (fildes[i] == '\0')
			break ;
		to_close = ft_atoi(&fildes[i], data);
		if (to_close)
			close(to_close);
		while (fildes[i] && fildes[i] != '.')
			i++;
	}
}

char	*append_fdes(t_shell *data, int new)
{
	char	*fds;
	char	*to_add;

	fds = data->fildes;
	to_add = ft_itoa(new, LOOP, data);
	to_add = ft_strjoin(".", to_add, LOOP, data);
	fds = ft_strjoin(fds, to_add, LOOP, data);
	return (fds);
}
