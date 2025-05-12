
#include "../../minishell.h"

static void	ft_dup_it(int fd_in, int fd_out, char *file, t_shell *data)
{
	if (fd_in != -44)
	{
		if (dup2(fd_in, 0) == -1)
		{
			fds_error(data, "Dup2() call failure[099]\n");
			if (data->unlink_it)
				unlink(file);
			return ;
		}
	}
	close(fd_in);
	if (data->unlink_it)
		unlink(file);
	if (fd_out != -44)
	{
		if (dup2(fd_out, 1) == -1)
		{
			fds_error(data, "Dup2() call failure[097]\n");
			return ;
		}
	}
	close(fd_out);
}

int	in_redirs(t_redir *in, int *flag, char **file, t_shell *data)
{
	int	fd_in;

	fd_in = -44;
	if (!ft_strcmp(in->type, "<"))
	{
		fd_in = redir_in(in);
		if (fd_in == -1)
			return (-1);
	}
	else
	{
		fd_in = heredoc_in(data, flag, file, in);
		if (fd_in == -1)
			return (-1);
	}
	data->fildes = append_fdes(data, fd_in);
	return (fd_in);
}

int	out_redirs(t_redir *in, t_shell *data)
{
	int	fd_out;

	fd_out = -44;
	if (!ft_strcmp(in->type, ">>"))
		fd_out = open(in->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (!ft_strcmp(in->type, ">") && ft_strcmp(in->file, ""))
		fd_out = open(in->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (check_empty_str(in->file, data))
		return (-1);
	if (fd_out == -1)
	{
		if (is_a_dir(in->file))
			return (-1);
		perror(in->file);
		return (-1);
	}
	data->fildes = append_fdes(data, fd_out);
	return (fd_out);
}

void	init_stuff(int *flag, char **file, int *fd_in, int *fd_out)
{
	*flag = 0;
	*file = NULL;
	*fd_in = -44;
	*fd_out = -44;
}

int	handle_redirs(t_redir *in, t_shell *data, int dup_it)
{
	int		fd_in;
	int		fd_out;
	char	*file;

	init_stuff(&data->unlink_it, &file, &fd_in, &fd_out);
	while (in)
	{
		if (!ft_strcmp_b(in->type, "<") || !ft_strcmp_b(in->type, "<<"))
		{
			fd_in = in_redirs(in, &data->unlink_it, &file, data);
			if (fd_in < 0)
				return (-1);
		}
		else
		{
			fd_out = out_redirs(in, data);
			if (fd_out < 0)
				return (-1);
		}
		in = in->next;
	}
	if (dup_it)
		ft_dup_it(fd_in, fd_out, file, data);
	return (0);
}
