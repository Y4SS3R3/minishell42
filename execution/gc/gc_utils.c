/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:44:17 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 11:34:36 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_trash	*gc_last(t_trash *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void	gc_add(t_trash **head, t_trash *new)
{
	t_trash	*last;

	if (!new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = gc_last(*head);
		if (last)
			last->next = new;
	}
}

t_trash	*gc_new(void *address, t_shell *data)
{
	t_trash	*new;

	new = malloc(sizeof(t_trash));
	if (!new)
	{
		data->free_it = 0;
		free_command(data, NULL);
	}
	new->to_free = address;
	new->freed = 0;
	new->next = NULL;
	return (new);
}

void	gc_free(t_shell *data, int mode)
{
	t_trash	*head;

	if (mode == LOOP)
		head = data->l_gc;
	else
		head = data->g_gc;
	while (head)
	{
		if (!head->freed && head->to_free)
		{
			free(head->to_free);
			head->to_free = NULL;
			head->freed = 1;
		}
		head = head->next;
	}
}
