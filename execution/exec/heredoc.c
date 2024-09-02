/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:12:48 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/02 13:40:14 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*bring_sign_back(char *limiter, t_shell *data)
{
	char	*res;

	res = limiter;
	if (ft_strnstr(limiter, data->key2, ft_strlen(limiter)))
		res = replace_key(limiter, data->key2, data);
	if (ft_strnstr(limiter, data->key, ft_strlen(limiter)))
		res = replace_key(limiter, data->key, data);
	return (res);
}

static void	fill_hdc_file(char *file, char *final, t_fd *node, t_shell *data)
{
	int	hdc;

	hdc = open_hdc(file, node, data);
	if (final)
		write(hdc, final, ft_strlen(final));
	close(hdc);
}

static char	*buffer_file_content(char *limiter, t_shell *data)
{
	char	*tmp;
	char	*final;

	final = NULL;
	while (!g_sig)
	{
		signal(SIGINT, ctrl_c_heredoc);
		tmp = fill_heredoc(limiter, data);
		if (tmp == NULL)
			break ;
		final = ft_strjoin(final, tmp, LOOP, data);
	}
	return (final);
}

int	heredoc(char *limiter, t_fd *node, t_shell *data)
{
	int		hdc;
	char	*tmp;
	char	*file;
	char	*final;
	int		fd;

	fd = dup(0);
	tmp = limiter;
	limiter = remove_quotes(limiter, data);
	if (!ft_strcmp(tmp, limiter))
		node->ex_flag = 1;
	limiter = bring_sign_back(limiter, data);
	final = buffer_file_content(limiter, data);
	if (hrdc_ctrlc(fd, data) == CTRLC_HRDC)
		return (CTRLC_HRDC);
	file = randomize_file_name(data);
	fill_hdc_file(file, final, node, data);
	hdc = end_hdc(fd, file, data);
	return (hdc);
}
