/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_make_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:46:12 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:47:35 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	mz_d_quote(t_token *list, t_list **head)
{
	char	*s;
	char	*tmp;

	s = NULL;
	s = ft_strjoin(s, "\"");
	(*head) = (*head)->next;
	while ((*head) && (*head)->nature != '\"')
	{
		tmp = s;
		s = ft_strjoin(s, (*head)->s);
		free(tmp);
		(*head) = (*head)->next;
	}
	tmp = s;
	s = ft_strjoin(s, "\"");
	free(tmp);
	(*head) = (*head)->next;
	list->args = mz_arr(list->args, NULL, s, 1);
}

static void	mz_quote(t_token *list, t_list **head)
{
	char	*s;
	char	*tmp;

	s = NULL;
	s = ft_strjoin(s, "\'");
	(*head) = (*head)->next;
	while ((*head) && (*head)->nature != '\'')
	{
		tmp = s;
		s = ft_strjoin(s, (*head)->s);
		free(tmp);
		(*head) = (*head)->next;
	}
	tmp = s;
	s = ft_strjoin(s, "\'");
	free(tmp);
	(*head) = (*head)->next;
	list->args = mz_arr(list->args, NULL, s, 1);
}

static void	mz_simple(t_token *list, t_list **head)
{
	char *s;
	char *tmp;

	s = NULL;
	while ((*head) && ((*head)->nature == 32 || (*head)->nature == -1))
	{
		tmp = s;
		if ((*head)->nature == 32)
		{
			s = ft_strjoin(s, " ");
			while ((*head) && (*head)->nature == 32)
				(*head) = (*head)->next;
		}
		if ((*head) && ((*head)->nature == -1))
			s = ft_strjoin(s, (*head)->s);
		else
			break ;
		free(tmp);
		(*head) = (*head)->next;
	}
	list->args = mz_arr(list->args, NULL, s, 1);
}

void	mz_make_cmd(t_token **list, t_list **head)
{
	char *s;
	t_token	*new;


	s = NULL;
	new = ft_lstnew((*head)->s);
	ft_lstadd_back(list, new, NULL);
	new->nature = (*head)->nature;
	(*head) = (*head)->next;
	while ((*head))
	{
	while ((*head) && (*head)->nature == 32)
		(*head) = (*head)->next;
	if ((*head) && (*head)->nature == -1)
		mz_simple(new, head);
	else if ((*head) && (*head)->nature == '\'')
		mz_quote(new, head);
	else if ((*head) && (*head)->nature == '\"')
		mz_d_quote(new, head);
	else
		break ;
	}
}

// echo appah "lol > this" 'haha ls > fuck' ss ll > tex.txt | ls -l -a | pwd

	// while ((*head))
	// {
	// 	printf("%s --> %i\n", (*head)->s, (*head)->nature);
	// 	(*head) = (*head)->next;
	// }




// 	void	mz_make_cmd(t_token **list, t_list **head)
// {
// 	char *s;
// 	char *tmp;


// 	s = NULL;

// 	ft_lstadd_back(list, ft_lstnew((*head)->s), NULL);
// 	(*head) = (*head)->next;
// 	printf("\nAppaaaaaaaah\n");
// 	while ((*head))
// 	{
// 		while ((*head)->nature == 32)
// 			(*head) = (*head)->next;
// 		if ((*head)->nature == -1)
// 			mz_simple(list, head);
// 		else if ((*head)->nature == '\'')
// 			mz_quote(list, head);
// 		else if ((*head)->nature == '\"')
// 			mz_d_quote(list, head);
// 		else
// 			break ;
// 	}
// }
