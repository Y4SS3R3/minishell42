/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:54:01 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/15 17:59:27 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*mz_first_scan(char *s, t_shell *data)
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
			i = make_space_nd(&head, s, i, data);
		else if (mz_is_special(s[i]))
			i = make_special_nd(&head, s, i, data);
		else
			i = make_word_nd(&head, s, i, data);
	}
	return (head);
}

t_token	*mz_parser(char *s, int *status, t_shell *data)
{
	t_list	*head;
	t_token	*list;

	if (mz_syntax_err(s) == 1)
	{
		(*status) = 258;
		return (NULL);
	}
	if (mz_syntax_err2(s) == 1)
	{
		(*status) = 258;
		return (NULL);
	}
	head = mz_first_scan(s, data);
	if (mz_syntax_handler(head) == -1)
	{
		(*status) = 258;
		return (NULL);
	}
	
	// t_list *tmp;
	// if (mz_syntax_handler(head) == -1)
	// 	return (NULL);
	// tmp = head;
	// while (head)
	// {
	// 	printf("%s  --> %i\n", head->s, head->nature);
	// 	head = head->next;
	// }
	// head = tmp;
	// exit(1);
	

	list = mz_last_scan(head, data);
	
	// t_token *linked = list;
	// int i;
	// while (linked)
	// {
	// 	i = 0;
	// 	printf("Join: %i", linked->join);
	// 	printf("\n\n%s  --> %i\n", linked->cmd, linked->nature);
	// 	while (linked->args && linked->args[i])
	// 	{
	// 		printf("arg_%i ->> [%s]\n", i, linked->args[i]);
	// 		i++;
	// 	}
	// 	linked = linked->next;
	// }
	// exit(1);


	mz_splitter(list, data);
	return (list);
}
