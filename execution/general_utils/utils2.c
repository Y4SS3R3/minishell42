/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:46:08 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/29 14:46:08 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

t_token	*token_clone(t_token *token, t_shell *data)
{
	t_token	*head;

	head = NULL;
	if (token == NULL)
		return (NULL);
	head = which_malloc(LOOP, sizeof(t_token), data);
	head->cmd = token->cmd;
	head->args = token->args;
	head->nature = token->nature;
	head->join = token->join;
	head->next = NULL;
	head->previous = NULL;
	head->right = token->right;
	head->left = token->left;
	return (head);
}

t_token	*ft_lstnew(char *cmd, int mode, t_shell *data)
{
	t_token	*head;

	head = which_malloc(mode, sizeof(t_token), data);
	head->next = NULL;
	head->previous = NULL;
	head->right = NULL;
	head->left = NULL;
	head->cmd = cmd;
	head->args = NULL;
	head->before = NULL;
	head->after = NULL;
	return (head);
}

t_token	*ft_lstlast(t_token *lst)
{
	t_token	*current;

	current = lst;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	ft_lstadd_back(t_token **lst, t_token *new, t_token *pre)
{
	t_token	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		new->previous = pre;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->previous = last;
	}
}
