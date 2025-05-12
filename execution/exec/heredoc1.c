
#include "../../minishell.h"

void	assign_hdc(t_fd *fds, t_token *infix)
{
	while (infix)
	{
		if (!ft_strcmp(infix->cmd, "<<"))
		{
			infix->hdc = fds;
			if (fds)
				fds = fds->next;
		}
		infix = infix->next;
	}
}

static void	count_heredoc(t_token *infix, t_shell *data)
{
	int	count;

	count = 0;
	while (infix)
	{
		if (!ft_strcmp(infix->cmd, "<<"))
			count++;
		infix = infix->next;
	}
	if (count > 16)
	{
		putstr_fd("starshell: maximum here-document count exceeded\n", 2);
		improved_exit(2, data);
	}
}

t_fd	*generate_heredoc(t_token *infix, t_shell *data)
{
	t_fd	*head;
	t_fd	*new;

	head = NULL;
	count_heredoc(infix, data);
	while (infix)
	{
		if (!ft_strcmp(infix->cmd, "<<"))
		{
			new = fds_new(data);
			if (new == NULL)
			{
				putstr_fd("ERROR IN FDS[113]\n", 2);
				return (NULL);
			}
			new->fd = heredoc(infix->args[0], new, data);
			new->limiter = infix->args[0];
			if (new->fd == CTRLC_HRDC || new->fd == -1)
				return (NULL);
			fds_addback(&head, new);
		}
		infix = infix->next;
	}
	return (head);
}

int	heredocing_time_cmd(t_shell *data, char **file, t_redir *heredoc)
{
	int	hdc_fd;

	hdc_fd = -1;
	if (heredoc)
		hdc_fd = ex_heredoc(heredoc->hdc, file, data);
	return (hdc_fd);
}

int	heredocing_time(t_shell *data, char **file)
{
	int	hdc;

	hdc = -1;
	if (data->fds)
		hdc = ex_heredoc(data->fds, file, data);
	return (hdc);
}
