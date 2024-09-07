/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_syntax_handler2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:42:05 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/07 18:03:40 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	mz_check_prev(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp->prev)
		tmp = tmp->prev;
	while (tmp->prev && tmp->nature == ' ')
		tmp = tmp->prev;
	if (tmp->nature == -1 || tmp->nature == ')')
		return (0);
	return (1);
}

static int	mz_check_after(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp)
		tmp = tmp->next;
	while (tmp && tmp->nature == ' ')
		tmp = tmp->next;
	if (tmp && (tmp->nature == -1 || tmp->nature == '<' || tmp->nature == '>'
			|| tmp->nature == '('))
		return (0);
	return (1);
}

int	mz_check_op(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		while (tmp && tmp->nature == ' ')
			tmp = tmp->next;
		if (tmp && (tmp->nature == '|' || tmp->nature == 76
				|| tmp->nature == 248))
		{
			if (mz_check_prev(tmp) == 1)
				return (-1);
			if (mz_check_after(tmp) == 1)
				return (-1);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}
