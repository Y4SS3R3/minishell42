/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_make_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:47:38 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/08 16:35:51 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mz_make_special(t_token **list, t_list **head, t_shell *data)
{
	t_token	*new;

	new = NULL;
	if ((*head)->nature == '<' || (*head)->nature == '>')
		mz_make_redi(list, head, data);
	else
	{
		new = ft_lstnew_mz((*head)->s, data);
		ft_lstadd_back(list, new, NULL);
		new->nature = (*head)->nature;
		(*head) = (*head)->next;
	}
}
