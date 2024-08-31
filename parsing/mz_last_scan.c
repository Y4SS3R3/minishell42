/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_last_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:12:44 by mzouine           #+#    #+#             */
/*   Updated: 2024/08/31 21:13:44 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*mz_last_scan(t_list *head)
{
	t_token	*list;

	list = NULL;
	while (head)
	{
		if (head->nature == -1)
			mz_make_cmd(&list, &head);
		else if (head->nature == 32)
			head = head->next;
		else
			mz_make_special(&list, &head);
	}
	return (list);
}
