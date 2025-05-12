
#include "../../minishell.h"

t_list	*ym_lstlast(t_list *lst)
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

void	ym_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = ym_lstlast(*lst);
	ptr->next = new;
	new->prev = ptr;
}

t_list	*ym_lstnew(char *content, int mode, t_shell *data)
{
	t_list	*new;

	if (content == NULL)
		return (NULL);
	new = which_malloc(mode, sizeof(t_list), data);
	new->s = ft_strdup(content, mode, data);
	new->next = NULL;
	new->prev = NULL;
	new->key_q = NULL;
	new->hide = 0;
	new->key_d_q = NULL;
	new->quote = 0;
	new->d_quote = 0;
	return (new);
}

t_list	*mz_lstnew(char *content, int mode, t_shell *data)
{
	t_list	*new;

	new = which_malloc(mode, sizeof(t_list), data);
	new->s = ft_strdup(content, mode, data);
	new->next = NULL;
	new->prev = NULL;
	new->key_q = NULL;
	new->hide = 0;
	new->key_d_q = NULL;
	new->quote = 0;
	new->d_quote = 0;
	return (new);
}
