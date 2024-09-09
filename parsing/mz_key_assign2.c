/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_key_assign2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:25:44 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/09 17:54:53 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	mz_count_sz(char *s, char *key)
{
	int	i;
	int	j;
	int	flag;
	int	size;

	i = 0;
	j = 0;
	flag = 0;
	while (s[i])
	{
		flag = mz_flag(s[i], flag);
		if (flag == 0 && s[i] == '*')
			j++;
		i++;
	}
	size = ft_strlen_mz(s) + (j * ft_strlen_mz(key)) + 1;
	return (size);
}

static int	mz_ctrl_c_v(char *key, char *final, int j)
{
	int	i;

	i = 0;
	while (key[i])
	{
		final[j] = key[i];
		j++;
		i++;
	}
	return (j);
}

char	*mz_key_assign2(char *s, char *key, t_shell *data)
{
	char	*final;
	int		i;
	int		flag;
	int		j;

	i = 0;
	j = 0;
	flag = 0;
	final = which_malloc(LOOP, mz_count_sz(s, key), data);
	if (!final)
		return (NULL);
	while (s[i])
	{
		flag = mz_flag(s[i], flag);
		if (flag == 0 && s[i] == '*')
			j = mz_ctrl_c_v(key, final, j);
		else
			final[j++] = s[i];
		i++;
	}
	final[j] = '\0';
	// mz_free_char(key);
	return (final);
}
