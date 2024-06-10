/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:45:44 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 10:23:28 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_stack_s(t_token *stack)
{
	while (stack)
	{
		printf("%s ", stack->cmd);
		stack = stack->next;
	}
	printf("\n");
}

t_token	*token_clone(t_token *token)
{
	t_token	*head;

	head = NULL;
	head = (t_token *)ft_calloc(1, sizeof(t_token));
	if (head == NULL)
		return (NULL);
	head->cmd = token->cmd;
	head->args = token->args;
	head->nature = token->nature;
	head->next = NULL;
	head->previous = NULL;
	head->right = token->right;
	head->left = token->left;
	return (head);
}

t_token	*ft_lstnew(char *cmd)
{
	t_token	*head;

	head = NULL;
	head = (t_token *)ft_calloc(1, sizeof(t_token));
	if (head == NULL)
		return (NULL);
	head->next = NULL;
	head->previous = NULL;
	head->cmd = cmd;
	head->args = NULL;
	head->right = NULL;
	head->left = NULL;
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
