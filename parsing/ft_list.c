/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:33:34 by mzouine           #+#    #+#             */
/*   Updated: 2024/08/29 15:40:44 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*mz_lstlast(t_list *lst)
{
	t_list *tmp;
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

t_list	*mz_lstnew(char *content, int mode, t_shell *data)
{
	t_list	*new;

	if (mode == GLOBAL)
		new = malloc_p(sizeof(t_list), data->g_gc, data);
	else if (mode == LOOP)
		new = malloc_p(sizeof(t_list), data->l_gc, data);
	else
	 	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new -> s = ft_strdup(content, mode, data);
	new -> next = NULL;
	new->prev = NULL;
	new->key_q = NULL;
	new->hide = 0;
	new->key_d_q = NULL;
	new->quote = 0;
	new->d_quote = 0;
	return (new);
}
