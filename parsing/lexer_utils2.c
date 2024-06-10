/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:17:09 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:47:57 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_dquote(t_list **head, char *s, int i)
{
	t_list	*new;
	char	*str;

	if (s[i + 1] == '\"')
	{
		str = ft_substr(s, i, 2);
		new = mz_lstnew(str);
		new->nature = 68;
		i = i + 2;
	}
	else
	{
		str = ft_substr(s, i, 1);
		new = mz_lstnew(str);
		new->nature = '\"';
		i = i + 1;
	}
	free(str);
	mz_lstadd_back(head, new);
	return (i);
}

int	make_dollar(t_list **head, char *s, int i)
{
	t_list	*new;
	char	*str;

	if (s[i + 1] == '$')
	{
		str = ft_substr(s, i, 2);
		new = mz_lstnew(str);
		new->nature = 72;
		i = i + 2;
	}
	else
	{
		str = ft_substr(s, i, 1);
		new = mz_lstnew(str);
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
	new = mz_lstnew(str);
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
	new = mz_lstnew(str);
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
	new = mz_lstnew(str);
	new->nature = '*';
	i = i + 1;
	free(str);
	mz_lstadd_back(head, new);
	return (i);
}
