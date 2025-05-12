
#include "../../minishell.h"

void	free_token(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmd);
		free(tmp);
		tmp = NULL;
	}
}

void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_trash(t_trash *head)
{
	t_trash	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_fds(t_fd *head)
{
	t_fd	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
}
