/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:27:40 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 10:24:02 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redir	*last_redir(t_redir *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

t_redir	*token_to_redir(t_token *token)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = token->cmd;
	redir->file = token->args[0];
	redir->next = NULL;
	return (redir);
}

void	append_redir(t_redir **head, t_redir *new)
{
	t_redir	*last;

	if (!new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = last_redir(*head);
		last->next = new;
	}
}

t_redir	*redir(t_token **input, int check1, int check2)
{
	t_redir	*redir;

	redir = NULL;
	while (*input && ((*input)->nature == check1 || (*input)->nature == check2))
	{
		append_redir(&redir, token_to_redir(*input));
		*input = (*input)->next;
	}
	return (redir);
}
