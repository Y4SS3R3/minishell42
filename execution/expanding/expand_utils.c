/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:41:57 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/04 17:11:49 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static char	*new_str(int index, char *input, t_shell *data)
// {
// 	int		j;
// 	char	*res;
// 	int		len;

// 	j = index;
// 	len = 0;
// 	while (input[index] != 0)
// 	{
// 		index++;
// 		len++;
// 	}
// 	if (ft_strlen(input) && (input[index - 1] == '"'
// 			|| input[index - 1] == '\''))
// 		len--;
// 	res = malloc_p(len + 1, data->l_gc, data);
// 	index = j;
// 	j = 0;
// 	while (j < len)
// 	{
// 		res[j] = input[index];
// 		j++;
// 		index++;
// 	}
// 	res[j] = 0;
// 	return (res);
// }

int	check_for_quotes(char *str)
{
	int		len;
	char	first;
	char	last;

	len = ft_strlen(str);
	if (len < 2)
		return (0);
	first = str[0];
	last = str[len - 1];
	if ((first == '\'' && last == '\'') || (first == '"' && last == '"'))
		return (1);
	return (0);
}

void	ex_remove_quotes(t_token *node, t_shell *data)
{
	int		i;
	t_redir	*before;
	t_redir	*after;

	i = 0;
	node->cmd = remove_quotes(node->cmd, data);
	before = node->before;
	after = node->after;
	while (node->args && node->args[i])
	{
		node->args[i] = remove_quotes(node->args[i], data);
		i++;
	}
	while (before)
	{
		before->file = remove_quotes(before->file, data);
		before = before->next;
	}
	while (after)
	{
		after->file = remove_quotes(after->file, data);
		after = after->next;
	}
}
