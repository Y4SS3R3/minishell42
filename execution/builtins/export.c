/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:44:03 by marvin            #+#    #+#             */
/*   Updated: 2024/08/31 19:15:10 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export(int ac, char **av, t_shell *data)
{
	if (ac == 0)
		print_export(data->envl);
	else
		return (export_var(ac, av, data));
	return (0);
}
