/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:17:09 by mzouine           #+#    #+#             */
/*   Updated: 2024/07/31 17:14:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_dquote(t_list **head, char *s, int i)
{
	t_list	*new;
	char	*str;
	int		tmp;

	if (s[i + 1] == '\"')
	{
		str = ft_substr(s, i, 2);
		new = mz_lstnew(str, -1, NULL);
		new->nature = -1;
		tmp = i + 2;
	}
	else
	{
		tmp = mz_search(s, i, '\"');
		if (tmp == -1)
			tmp = 1;
		str = ft_substr(s, i, tmp - i);
		// if (str[ft_strlen(str) - 1] == 32)
		// 	str[ft_strlen(str) - 1] = '\0';
		new = mz_lstnew(str, -1, NULL);
		new->nature = -1;
	}
	free(str);
	mz_lstadd_back(head, new);
	return (tmp);
}

int	make_dollar(t_list **head, char *s, int i)
{
	t_list	*new;
	char	*str;

	if (s[i + 1] == '$')
	{
		str = ft_substr(s, i, 2);
		new = mz_lstnew(str, -1, NULL);
		new->nature = 72;
		i = i + 2;
	}
	else
	{
		str = ft_substr(s, i, 1);
		new = mz_lstnew(str, -1, NULL);
		new->nature = '$';
		i = i + 1;
	}
	free(str);
	mz_lstadd_back(head, new);
	return (i);
}

int	make_o_par(t_list **head, char *s, int i)
{
	t_list	*new;
	char	*str;

	str = ft_substr(s, i, 1);
	new = mz_lstnew(str, -1, NULL);
	new->nature = '(';
	i = i + 1;
	free(str);
	mz_lstadd_back(head, new);
	return (i);
}

int	make_c_par(t_list **head, char *s, int i)
{
	t_list	*new;
	char	*str;

	str = ft_substr(s, i, 1);
	new = mz_lstnew(str, -1, NULL);
	new->nature = ')';
	i = i + 1;
	free(str);
	mz_lstadd_back(head, new);
	return (i);
}

int	make_star(t_list **head, char *s, int i)
{
	t_list	*new;
	char	*str;

	str = ft_substr(s, i, 1);
	new = mz_lstnew(str, -1, NULL);
	new->nature = '*';
	i = i + 1;
	free(str);
	mz_lstadd_back(head, new);
	return (i);
}
