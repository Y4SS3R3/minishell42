/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fildes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:47:10 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/09 19:24:42 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fildes(t_shell *data)
{
	char	*fildes;
	int		i;
	int		to_close;

	fildes = data->fildes;
	i = 0;
	if (fildes == NULL)
		return ;
	while (fildes[i])
	{
		while (fildes[i] && fildes[i] == '.')
			i++;
		if (fildes[i] == '\0')
			break ;
		to_close = ft_atoi(&fildes[i]);
		if (to_close)
			close(to_close);
		while (fildes[i] && fildes[i] != '.')
			i++;
	}
}

char	*append_fdes(t_shell *data, int new)
{
	char	*fds;
	char	*to_add;

	fds = data->fildes;
	to_add = ft_itoa(new, LOOP, data);
	to_add = ft_strjoin(".", to_add, LOOP, data);
	fds = ft_strjoin(fds, to_add, LOOP, data);
	return (fds);
}
