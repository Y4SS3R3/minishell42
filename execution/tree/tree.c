/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:08:22 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/03 15:08:22 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*command_unit2(t_token **input,
		t_shell *data, t_token	*left, t_redir *before)
{
	t_redir	*after;

	left = token_clone(*input, data);
	left->before = before;
	*input = (*input)->next;
	after = redir(input, data);
	left->after = after;
	return (left);
}

static t_token	*command_unit(t_token **input, t_shell *data)
{
	t_redir	*before;
	t_redir	*after;
	t_token	*left;
	t_token	*tmp;

	before = NULL;
	after = NULL;
	left = NULL;
	tmp = *input;
	if ((*input)->nature == OPEN_PAR)
	{
		*input = (*input)->next;
		left = ft_tree(input, data);
		return (left);
	}
	before = redir(input, data);
	if (!(*input) || ((*input)->nature != WORD))
	{
		left = token_clone(tmp, data);
		left->before = before;
		left->after = after;
		return (left);
	}
	return (command_unit2(input, data, left, before));
}

static t_token	*pipe_unit(t_token **input, t_shell *data)
{
	t_token	*left;
	t_token	*right;
	t_token	*pipe;

	pipe = NULL;
	left = command_unit(input, data);
	while (*input && (*input)->nature == PIPE)
	{
		pipe = token_clone(*input, data);
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
		op = token_clone(*control, data);
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
