
#include "../../minishell.h"

void	fds_addback(t_fd **head, t_fd *new)
{
	t_fd	*last;

	if (!new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = fds_last(*head);
		if (last)
			last->next = new;
	}
}

t_fd	*fds_last(t_fd *lst)
{
	t_fd	*current;

	current = lst;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

t_fd	*fds_new(t_shell *data)
{
	t_fd	*new;

	new = which_malloc(LOOP, sizeof(t_fd), data);
	new->fd = -1;
	new->ex_flag = 0;
	new->limiter = NULL;
	new->file_name = NULL;
	new->next = NULL;
	new->visited = 0;
	return (new);
}
