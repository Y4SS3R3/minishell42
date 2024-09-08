/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_nul_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:20:11 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/08 16:37:23 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned int	mz_word_count(const char *s, char c, int n)
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

static char	*mz_word_finder(const char *s, char c, int *word, int n, t_shell *data)
{
	int		i;
	int		j;
	char	*str;

	while (*word < n && s[*word] == c)
		(*word)++;
	i = *word;
	while (*word < n && s[*word] != c)
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

	if (!s)
		return (NULL);
	word = 0;
	i = 0;
	final = which_malloc(LOOP, (mz_word_count(s, c, n) + 1) * sizeof(char *), data);
	if (!final)
		return (NULL);
	while (i < mz_word_count(s, c, n))
	{
		final[i] = mz_word_finder(s, c, &word, n, data);
		i++;
		word++;
	}
	final[i] = NULL;
	return (final);
}
