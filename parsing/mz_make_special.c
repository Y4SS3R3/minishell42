/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_make_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:47:38 by mzouine           #+#    #+#             */
/*   Updated: 2024/07/31 18:15:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mz_make_special(t_token **list, t_list **head)
{
	t_token *new;

	new = NULL;

	if ((*head)->nature == '<' || (*head)->nature == '>')
		mz_make_redi(list, head);
	else
	{
		new = ft_lstnew((*head)->s, -1, NULL);
		ft_lstadd_back(list, new, NULL);
		new->nature = (*head)->nature;
		(*head) = (*head)->next;
	}
}
