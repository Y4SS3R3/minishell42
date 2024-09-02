/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_make_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:46:12 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/02 17:48:21 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	mz_d_quote(t_token *list, t_list **head)
{
	char	*s;
	char	*tmp;

	s = NULL;
	s = ft_strjoin_mz(s, "\"");
	(*head) = (*head)->next;
	while ((*head) && (*head)->nature != '\"')
	{
		tmp = s;
		s = ft_strjoin_mz(s, (*head)->s);
		free(tmp);
		(*head) = (*head)->next;
	}
	tmp = s;
	s = ft_strjoin_mz(s, "\"");
	free(tmp);
	if (*head)
		(*head) = (*head)->next;
	list->args = mz_arr(list->args, NULL, s, 1);
}

static void	mz_quote(t_token *list, t_list **head)
{
	char	*s;
	char	*tmp;

	s = NULL;
	s = ft_strjoin_mz(s, "\'");
	(*head) = (*head)->next;
	while ((*head) && (*head)->nature != '\'')
	{
		tmp = s;
		s = ft_strjoin_mz(s, (*head)->s);
		free(tmp);
		(*head) = (*head)->next;
	}
	tmp = s;
	s = ft_strjoin_mz(s, "\'");
	free(tmp);
	if (*head)
		(*head) = (*head)->next;
	list->args = mz_arr(list->args, NULL, s, 1);
}

static void	mz_simple(t_token *list, t_list **head)
{
	char	*s;
	char	*tmp;

	s = NULL;
	while ((*head) && ((*head)->nature == 32 || (*head)->nature == -1))
	{
		tmp = s;
		if ((*head)->nature == 32)
		{
			s = ft_strjoin_mz(s, " ");
			while ((*head) && (*head)->nature == 32)
				(*head) = (*head)->next;
		}
		if ((*head) && ((*head)->nature == -1))
			s = ft_strjoin_mz(s, (*head)->s);
		else
			break ;
		free(tmp);
		(*head) = (*head)->next;
	}
	list->args = mz_arr(list->args, NULL, s, 1);
}

void	mz_make_cmd(t_token **list, t_list **head)
{
	char	*s;
	t_token	*new;

	s = NULL;
	new = ft_lstnew_mz((*head)->s);
	ft_lstadd_back(list, new, NULL);
	new->nature = (*head)->nature;
	new->key_d_q = (*head)->key_d_q;
	new->key_q = (*head)->key_q;
	(*head) = (*head)->next;
	while ((*head))
	{
		while ((*head) && (*head)->nature == 32)
		{
			(*head) = (*head)->next;
			(*list)->join = 0;
		}
		if ((*head) && (*head)->nature == -1)
			mz_simple(new, head);
		else if ((*head) && (*head)->nature == '\'')
			mz_quote(new, head);
		else if ((*head) && (*head)->nature == '\"')
			mz_d_quote(new, head);
		else if ((*head) && ((*head)->nature == 60 || (*head)->nature == 62))
			mz_make_redi(list, head);
		else
			break ;
	}
}
