/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_splitter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:26:56 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/17 17:45:31 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*mz_nuller(t_token *head, int n)
{
	int		i;
	int		flag;
	char	*arr;

	i = 0;
	arr = head->args[n];
	flag = -1;
	while (arr[i])
	{
		if (flag == -1 && arr[i] == '\"')
			flag = 1;
		else if (flag == -1 && arr[i] == '\'')
			flag = 2;
		else
		{
			if (flag == -1 && arr[i] == 32)
				arr[i] = '\0';
			else if ((flag == 1 && arr[i] == '\"')
				|| (flag == 2 && arr[i] == '\''))
				flag = -1;
		}
		i++;
	}
	return (arr);
}

static char	***mz_triple_init(t_token *head, t_shell *data)
{
	t_token	*tmp;
	int		i;
	char	***final;

	i = 0;
	tmp = head;
	if (!head)
		return (NULL);
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	final = which_malloc(LOOP, (i + 1) * sizeof(char **), data);
	while (i >= 0)
	{
		final[i] = NULL;
		i--;
	}
	return (final);
}

void	mz_splitter(t_token *head, t_shell *data)
{
	t_token		*tmp;
	t_infozm	x;
	char		***a;
	int			j;

	tmp = head;
	a = mz_triple_init(head, data);
	j = 0;
	while (tmp)
	{
		x.i = 0;
		while (tmp && tmp->args && tmp->args[x.i])
		{
			x.l = ft_strlen_mz(tmp->args[x.i]);
			tmp->args[x.i] = mz_nuller(tmp, x.i);
			x.a = tmp->args[x.i];
			data->flag = 2;
			a[j] = mz_arr(a[j], mz_nl_sp(x.a, '\0', x.l, data), NULL, data);
			x.i = x.i + 1;
		}
		if (tmp && tmp->args)
			tmp->args = a[j];
		tmp = tmp->next;
		j++;
	}
}
