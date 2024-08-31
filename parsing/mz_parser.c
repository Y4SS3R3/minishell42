/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:54:01 by mzouine           #+#    #+#             */
/*   Updated: 2024/08/31 21:31:27 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*mz_first_scan(char *s)
{
	t_list	*head;
	int		i;

	i = 0;
	head = NULL;
	while (s[i])
	{
		if (s[i] == 32 && s[i + 1] == '\0')
			return (head);
		if (mz_is_space(s[i]))
			i = make_space_nd(&head, s, i);
		else if (mz_is_special(s[i]))
			i = make_special_nd(&head, s, i);
		else
			i = make_word_nd(&head, s, i);
	}
	return (head);
}

t_token	*mz_parser(char *s)
{
	t_list	*head;
	t_token	*list;

	if (mz_syntax_err(s) == 1)
		return (NULL);
	if (mz_syntax_err2(s) == 1)
		return (NULL);
	s = mz_joiner(s);
	head = mz_first_scan(s);
	if (mz_syntax_handler(head) == -1)
		return (NULL);
	// while (head)
	// {
	// 	printf("%s  --> %i", head->s, head->nature);
	// 	head = head->next;
	// }
	// exit(1);
	list = mz_last_scan(head);
	mz_splitter(list);
	return (list);
}
