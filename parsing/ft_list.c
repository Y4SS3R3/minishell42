
#include "../minishell.h"

t_list	*mz_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

void	mz_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = mz_lstlast(*lst);
	ptr->next = new;
	new->prev = ptr;
}

t_list	*mz_lstnew_mz(char *content, t_shell *data)
{
	t_list	*new;

	new = which_malloc(LOOP, sizeof(t_list), data);
	new -> s = ft_strdup_mz(content, data);
	new -> next = NULL;
	new->prev = NULL;
	new->key_q = NULL;
	new->key_d_q = NULL;
	new->quote = 0;
	new->d_quote = 0;
	return (new);
}
