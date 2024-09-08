/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:52:56 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/08 10:46:03 by ymassiou         ###   ########.fr       */
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
			if (env == NULL)
				break ;
			env->hide = 0;
			if (env->s)
				ym_lstadd_back(&head, env);
		}
		i++;
	}
	return (head);
}
