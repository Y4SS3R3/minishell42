
#include "../../minishell.h"

int	is_a_redir(t_token *root)
{
	if (root && (!ft_strcmp(root->cmd, "<")
			|| !ft_strcmp(root->cmd, ">")
			|| !ft_strcmp(root->cmd, ">>")
			|| !ft_strcmp(root->cmd, "<<")))
		return (1);
	return (0);
}

t_redir	*token_to_redir(t_token *token, t_shell *data)
{
	t_redir	*redir;

	redir = which_malloc(LOOP, sizeof(t_redir), data);
	redir->type = token->cmd;
	token->args[0] = token->args[0];
	redir->file = token->args[0];
	redir->hdc = token->hdc;
	redir->next = NULL;
	return (redir);
}

void	append_redir(t_redir **head, t_redir *new)
{
	t_redir	*last;

	if (!new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = last_redir(*head);
		last->next = new;
	}
}
