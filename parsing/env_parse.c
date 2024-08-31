/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:05:47 by mzouine           #+#    #+#             */
/*   Updated: 2024/08/29 13:08:31 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*env_parse(char **envp, t_shell *data)
{
	int		i;
	t_list	*env;
	t_list	*head;

	i = 0;
	head = NULL;
	env = NULL;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			env = mz_lstnew(envp[i], GLOBAL, data);
			env->hide = 0;
			if (env->s)
				ym_lstadd_back(&head, env);
		}
		i++;
	}
	return (head);
}
