/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:55:24 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/12 20:56:32 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mz_search(char *s, int i, char c)
{
	i += 1;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (-1);
}

t_token	*ft_lstnew_mz(char *cmd, t_shell *data)
{
	t_token	*head;

	head = NULL;
	head = which_malloc(LOOP, sizeof(t_token), data);
	if (head == NULL)
		return (NULL);
	head->args = NULL;
	head->next = NULL;
	head->previous = NULL;
	head->cmd = cmd;
	head->right = NULL;
	head->left = NULL;
	head->key_d_q = NULL;
	head->key_q = NULL;
	head->nature = 0;
	head->quote = 0;
	head->d_quote = 0;
	head->par = 0;
	head->join = 1;
	return (head);
}
