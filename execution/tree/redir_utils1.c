
#include "../../minishell.h"

t_redir	*last_redir(t_redir *head)
{
	t_redir	*current;

	current = head;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

t_redir	*redir(t_token **input, t_shell *data)
{
	t_redir	*redir;

	redir = NULL;
	while (*input && ((*input)->nature == HERE_DOC
			|| (*input)->nature == REDIR_IN
			|| (*input)->nature == REDIR_OUT
			|| (*input)->nature == APPEND
		))
	{
		append_redir(&redir, token_to_redir(*input, data));
		*input = (*input)->next;
	}
	return (redir);
}
