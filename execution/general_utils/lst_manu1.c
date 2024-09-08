/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manu1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:33:34 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/08 14:22:54 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!new)
		return (NULL);
	new->s = ft_strdup(content, mode, data);
	if (!new->s)
		return (NULL);
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
	if (!new)
		return (NULL);
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
