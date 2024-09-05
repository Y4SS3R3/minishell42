/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_make_redi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:46:10 by mzouine           #+#    #+#             */
/*   Updated: 2024/08/31 21:16:04 by ymassiou         ###   ########.fr       */
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
		{
			s = ft_strjoin_mz(s, (*head)->s);
			free(tmp);
			(*head) = (*head)->next;
			break ;
		}
		else
			break ;
		free(tmp);
		(*head) = (*head)->next;
	}
	list->args = mz_arr(list->args, NULL, s, 1);
}

void	mz_make_redi(t_token **list, t_list **head)
{
	t_token	*new;

	new = ft_lstnew_mz((*head)->s);
	ft_lstadd_back(list, new, NULL);
	new->nature = (*head)->nature;
	(*head) = (*head)->next;
	while ((*head) && (*head)->nature == 32)
		(*head) = (*head)->next;
	if ((*head) && (*head)->nature == -1)
		mz_simple(new, head);
	else if ((*head) && (*head)->nature == '\'')
		mz_quote(new, head);
	else if ((*head) && (*head)->nature == '\"')
		mz_d_quote(new, head);
}
