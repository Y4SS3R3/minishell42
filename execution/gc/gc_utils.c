/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:44:17 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 10:23:08 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_trash	*gc_last(t_trash *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	gc_add(t_trash **head, t_trash *new)
{
	t_trash	*last;

	if (!new)
		return ;
	if (!head)
		*head = new;
	else
	{
		last = gc_last(*head);
		last->next = new;
	}
}

t_trash	*gc_new(void *address)
{
	t_trash	*new;

	new = malloc(sizeof(t_trash));
	if (!new)
		return (new);
	new->to_free = address;
	new->next = NULL;
	return (new);
}

void	gc_free(t_shell *data)
{
	t_trash	*head;

	head = data->gc;
	while (head)
	{
		free(head->to_free);
		head = head->next;
	}
	head = data->gc;
	while (head)
	{
		free(head);
		head = head->next;
	}
}
