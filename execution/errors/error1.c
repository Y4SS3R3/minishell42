/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:22:13 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/12 22:25:11 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_err1(char *str, t_shell *data)
{
	if (str && ft_strchr(str, '/'))
		check_ifdir(str, data);
	exec_err(str);
}
