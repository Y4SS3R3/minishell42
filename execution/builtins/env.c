/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:32:24 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:56:49 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env(t_shell *data)
{
	t_list	*envl;

	envl = data->envl;
	while (envl)
	{
		if (envl->hide == 0)
			printf("%s\n", envl->s);
		envl = envl->next;
	}
	return (0);
}
