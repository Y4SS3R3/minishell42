/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:26:30 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/11 14:26:32 by ymassiou         ###   ########.fr       */
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
