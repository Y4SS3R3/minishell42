/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:16:05 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/31 14:45:08 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_token(t_list **head, t_list *to_remove)
{
	if (head == NULL || *head == NULL || to_remove == NULL)
		return ;
	if (to_remove == *head)
	{
		*head = (*head)->next;
		if (*head != NULL)
			(*head)->prev = NULL;
	}
	else
	{
		if (to_remove->prev != NULL)
			to_remove->prev->next = to_remove->next;
		if (to_remove->next != NULL)
			to_remove->next->prev = to_remove->prev;
	}
}

int	cmp_s(char *s1, char *s2)
{
	return (ft_strcmp(s1, s2));
}

void	ex_print_util(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		if (!flag && str[i] == '=')
		{
			flag = 1;
			write(1, "\"", 1);
		}
		i++;
	}
	if (flag)
		write(1, "\"", 1);
}

void	mini_print(t_list *envl)
{
	while (envl)
	{
		putstr_fd("declare -x ", 1);
		ex_print_util(envl->s);
		printf("\n");
		envl = envl->next;
	}
}

void	print_export(t_list *envl)
{
	t_list	*cur_i;
	t_list	*cur_j;
	char	*tmp;

	cur_i = envl;
	while (cur_i)
	{
		cur_j = cur_i->next;
		while (cur_j)
		{
			if (cmp_s(cur_i->s, cur_j->s) > 0)
			{
				tmp = cur_i->s;
				cur_i->s = cur_j->s;
				cur_j->s = tmp;
			}
			cur_j = cur_j->next;
		}
		cur_i = cur_i->next;
	}
	mini_print(envl);
}
