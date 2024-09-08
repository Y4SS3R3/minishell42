/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:17:09 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/08 16:41:00 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_dquote(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;
	int		tmp;

	if (s[i + 1] == '\"')
	{
		str = ft_substr_mz(s, i, 2, data);
		new = mz_lstnew_mz(str, data);
		new->nature = -1;
		tmp = i + 2;
	}
	else
	{
		tmp = mz_search(s, i, '\"');
		if (tmp == -1)
			tmp = 1;
		str = ft_substr_mz(s, i, tmp - i, data);
		new = mz_lstnew_mz(str, data);
		new->nature = -1;
	}
	mz_lstadd_back(head, new);
	return (tmp);
}

int	make_dollar(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;

	if (s[i + 1] == '$')
	{
		str = ft_substr_mz(s, i, 2, data);
		new = mz_lstnew_mz(str, data);
		new->nature = 72;
		i = i + 2;
	}
	else
	{
		str = ft_substr_mz(s, i, 1, data);
		new = mz_lstnew_mz(str, data);
		new->nature = '$';
		i = i + 1;
	}
	mz_lstadd_back(head, new);
	return (i);
}

int	make_o_par(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;

	str = ft_substr_mz(s, i, 1, data);
	new = mz_lstnew_mz(str, data);
	new->nature = '(';
	i = i + 1;
	mz_lstadd_back(head, new);
	return (i);
}

int	make_c_par(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;

	str = ft_substr_mz(s, i, 1, data);
	new = mz_lstnew_mz(str, data);
	new->nature = ')';
	i = i + 1;
	mz_lstadd_back(head, new);
	return (i);
}

int	make_star(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;

	str = ft_substr_mz(s, i, 1, data);
	new = mz_lstnew_mz(str, data);
	new->nature = '*';
	i = i + 1;
	mz_lstadd_back(head, new);
	return (i);
}
