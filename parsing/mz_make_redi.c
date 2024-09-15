/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_make_redi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:46:10 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/15 17:59:05 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	mz_d_quote(t_token *list, t_list **head, t_shell *data)
{
	char	*s;
	char	*tmp;

	s = NULL;
	s = ft_strjoin_mz(s, "\"", data);
	(*head) = (*head)->next;
	while ((*head) && (*head)->nature != '\"')
	{
		tmp = s;
		s = ft_strjoin_mz(s, (*head)->s, data);
		(*head) = (*head)->next;
	}
	tmp = s;
	s = ft_strjoin_mz(s, "\"", data);
	if (*head)
		(*head) = (*head)->next;
	data->flag = 1;
	list->args = mz_arr(list->args, NULL, s, data);
}

static void	mz_quote(t_token *list, t_list **head, t_shell *data)
{
	char	*s;
	char	*tmp;

	s = NULL;
	s = ft_strjoin_mz(s, "\'", data);
	(*head) = (*head)->next;
	while ((*head) && (*head)->nature != '\'')
	{
		tmp = s;
		s = ft_strjoin_mz(s, (*head)->s, data);
		(*head) = (*head)->next;
	}
	tmp = s;
	s = ft_strjoin_mz(s, "\'", data);
	if (*head)
		(*head) = (*head)->next;
	data->flag = 1;
	list->args = mz_arr(list->args, NULL, s, data);
}

static void	mz_simple(t_token *list, t_list **head, t_shell *data)
{
	char	*s;
	char	*tmp;

	s = NULL;
	if ((*head) && ((*head)->nature == 32 || (*head)->nature == -1))
	{
		tmp = s;
		if ((*head)->nature == 32)
		{
			s = ft_strjoin_mz(s, " ", data);
			while ((*head) && (*head)->nature == 32)
				(*head) = (*head)->next;
		}
		while ((*head) && ((*head)->nature == -1))
		{
			s = ft_strjoin_mz(s, (*head)->s, data);
			(*head) = (*head)->next;
			// if (!(s[mz_strlen(s) - 1] == '$' && ((*head)->s[0] == '\'' || (*head)->s[0] == '\"')))
			// 	break ;
		}
	}
	data->flag = 1;
	list->args = mz_arr(list->args, NULL, s, data);
}

void	mz_make_redi(t_token **list, t_list **head, t_shell *data)
{
	t_token	*new;

	new = ft_lstnew_mz((*head)->s, data);
	ft_lstadd_back(list, new, NULL);
	new->nature = (*head)->nature;
	(*head) = (*head)->next;
	while ((*head) && (*head)->nature == 32)
		(*head) = (*head)->next;
	if ((*head) && (*head)->nature == -1)
		mz_simple(new, head, data);
	else if ((*head) && (*head)->nature == '\'')
		mz_quote(new, head, data);
	else if ((*head) && (*head)->nature == '\"')
		mz_d_quote(new, head, data);
}
