
#include "../minishell.h"

void	mz_make_special(t_token **list, t_list **head, t_shell *data)
{
	t_token	*new;

	new = NULL;
	if ((*head)->nature == '<' || (*head)->nature == '>')
		mz_make_redi(list, head, data);
	else
	{
		new = ft_lstnew_mz((*head)->s, data);
		ft_lstadd_back(list, new, NULL);
		new->nature = (*head)->nature;
		(*head) = (*head)->next;
	}
}
