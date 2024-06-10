/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:08:26 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:46:52 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_space_nd(t_list **head, char *s, int i)
{
	t_list	*new;
	char	*str;
	int		n;

	new = NULL;
	str = NULL;
	n = i;
	while (mz_is_space(s[i]) && s[i])
		i++;
	str = ft_substr(s, n, i - n);
	new = mz_lstnew(str);
	free(str);
	new->nature = 32;
	mz_lstadd_back(head, new);
	return (i);
}


int	make_word_nd(t_list **head, char *s, int i)
{
	t_list	*new;
	char	*str;
	int		n;

	new = NULL;
	str = NULL;
	n = i;
	while (!mz_is_space(s[i]) && !mz_is_special(s[i]) && s[i])
		i++;
	str = ft_substr(s, n, i - n);
	new = mz_lstnew(str);
	free(str);
	new->nature = -1;
	mz_lstadd_back(head, new);
	return (i);
}

int	make_special_nd(t_list **head, char *s, int i)
{
	if (s[i] == '|')
		return (make_pipe(head, s, i));
	else if (s[i] == '>')
		return (make_in(head, s, i));
	else if (s[i] == '<')
		return (make_out(head, s, i));
	else if (s[i] == '&')
		return (make_and(head, s, i));
	else if (s[i] == '\'')
		return (make_quote(head, s, i));
	else if (s[i] == '\"')
		return (make_dquote(head, s, i));
	else if (s[i] == '$')
		return (make_dollar(head, s, i));
	else if (s[i] == '(')
		return (make_o_par(head, s, i));
	else if (s[i] == ')')
		return (make_c_par(head, s, i));
	else if (s[i] == '*')
		return (make_star(head, s, i));
	return (i);
}
