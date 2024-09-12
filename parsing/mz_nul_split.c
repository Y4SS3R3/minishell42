/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_nul_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:20:11 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/12 20:39:25 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned int	mz_wd_cnt(const char *s, char c, int n)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < n)
	{
		while (s[i] == c && i < n)
			i++;
		if (s[i] != c && i < n)
			j++;
		while (s[i] != c && i < n)
			i++;
	}
	return (j);
}

static char	*mz_word_finder(const char *s, t_infomz *mz,
		int *word, t_shell *data)
{
	int		i;
	int		j;
	char	*str;

	while (*word < mz->i && s[*word] == mz->c)
		(*word)++;
	i = *word;
	while (*word < mz->i && s[*word] != mz->c)
		(*word)++;
	str = which_malloc(LOOP, (*word - i) + 1, data);
	if (!str)
		return (NULL);
	j = 0;
	while (i + j < *word)
	{
		str[j] = s[j + i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	**mz_nl_sp(char const *s, char c, int n, t_shell *data)
{
	char			**final;
	unsigned int	i;
	int				word;
	t_infomz		*tmp;

	if (!s)
		return (NULL);
	word = 0;
	i = 0;
	final = which_malloc(LOOP, (mz_wd_cnt(s, c, n) + 1) * sizeof(char *), data);
	if (!final)
		return (NULL);
	while (i < mz_wd_cnt(s, c, n))
	{
		tmp->c = c;
		tmp->i = n;
		final[i] = mz_word_finder(s, tmp, &word, data);
		i++;
		word++;
	}
	final[i] = NULL;
	return (final);
}
