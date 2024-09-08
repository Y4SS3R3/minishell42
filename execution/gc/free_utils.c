/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:03:40 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/08 11:33:24 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_token(t_token *head)
{
	t_token	*tmp;
	int		i;

	i = 0;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmd);
		while (tmp->args && tmp->args[i])
		{
			free(tmp->args[i]);
			i++;
		}
		free(tmp->args);
		free(tmp);
		tmp = NULL;
	}
}

void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_trash(t_trash *head)
{
	t_trash	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_fds(t_fd *head)
{
	t_fd	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
}
