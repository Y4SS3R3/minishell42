/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:29:03 by ymassiou          #+#    #+#             */
/*   Updated: 2024/05/17 23:08:32 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*command_unit(t_token **input, t_shell *data)
{
	t_redir	*redirs_in;
	t_token	*left;

	if ((*input)->nature == OPEN_PAR)
	{
		*input = (*input)->next;
		left = ft_tree(input, data);
		return (left);
	}
	redirs_in = redir(input, REDIR_IN, HERE_DOC);
	left = token_clone(*input);
	left->redirs_in = redirs_in;
	*input = (*input)->next;
	left->redirs_out = redir(input, REDIR_OUT, APPEND);
	return (left);
}

t_token	*pipe_unit(t_token **input, t_shell *data)
{
	t_token	*left;
	t_token	*right;
	t_token	*pipe;

	pipe = NULL;
	left = command_unit(input, data);
	while (*input && (*input)->nature == PIPE)
	{
		pipe = token_clone(*input);
		*input = (*input)->next;
		right = pipe_unit(input, data);
		pipe->left = left;
		pipe->right = right;
	}
	if (pipe)
		return (pipe);
	return (left);
}

t_token	*ft_tree(t_token **control, t_shell *data)
{
	t_token	*left;
	t_token	*right;
	t_token	*op;

	op = NULL;
	left = pipe_unit(control, data);
	while (*control && ((*control)->nature == AND || (*control)->nature == OR))
	{
		op = token_clone(*control);
		*control = (*control)->next;
		right = pipe_unit(control, data);
		op->right = right;
		op->left = left;
		left = op;
	}
	if (*control && (*control)->nature == CLOSE_PAR)
		(*control) = (*control)->next;
	if (op)
		return (op);
	return (left);
}
