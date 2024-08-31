/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [DEPRECATED]print_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:07:31 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/29 22:00:38 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_list(t_list *head)
{
	while (head)
	{
		printf("[%s]\n", head->s);
		head = head->next;
	}
}

void print_2d_array(char **arr)
{
	int i = 0;
	if (arr == NULL)
	{
		puts("(NULL)");
		return ;
	}
	if (*arr == NULL)
	{
		puts("(NoLLos)");
		return ;
	}
	while (arr[i])
		printf("[%s]\n", arr[i++]);
}

void print2DUtil(t_token* root, int space)
{
	if (root == NULL)
		return;
	space += 10;
	print2DUtil(root->right, space);
	printf("\n");
	for (int i = 10; i < space; i++)
		printf(" ");
	printf("%s\n", root->cmd);
	print2DUtil(root->left, space);
}

void print2D(t_token* root)
{
	print2DUtil(root, 0);
}

void	print_stack(t_token *stack)
{
	while (stack)
	{
		dprintf(2, "[%s] NATURE [%d] ", stack->cmd, stack->nature);
		stack = stack->next;
	}
	printf("\n");
}

void	print_stack_s(t_token *stack)
{
	while (stack)
	{
		dprintf(2, "%s ", stack->cmd);
		stack = stack->next;
	}
	printf("\n");
}

void	print_fds(t_fd *head)
{
	while (head)
	{
		dprintf(2, "FILE [%s] FD[%d] LIMITER[%s]\n", head->file_name, head->fd, head->limiter);
		head = head->next;
	}
}
