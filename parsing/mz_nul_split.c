/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_nul_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:20:11 by mzouine           #+#    #+#             */
/*   Updated: 2024/07/09 19:44:34 by ymassiou         ###   ########.fr       */
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

static char	*mz_word_finder(const char *s, char c, int *word, int n)
{
	int		i;
	int		j;
	char	*str;

	while (*word < n && s[*word] == c)
		(*word)++;
	i = *word;
	while (*word < n && s[*word] != c)
		(*word)++;
	str = malloc((*word - i) + 1);
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

static char	**freemem(char **final)
{
	int	i;

	i = 0;
	if (final)
	{
		while (final[i])
		{
			free(final[i]);
			i++;
		}
		free(final);
	}
	return (NULL);
}

char	**mz_nl_sp(char const *s, char c, int n)
{
	char			**final;
	unsigned int	i;
	int				word;

	if (!s)
		return (NULL);
	word = 0;
	i = 0;
	final = malloc((mz_word_count(s, c, n) + 1) * sizeof(char *));
	if (!final)
		return (NULL);
	while (i < mz_word_count(s, c, n))
	{
		final[i] = mz_word_finder(s, c, &word, n);
		if (!final[i])
			return (freemem(final));
		i++;
		word++;
	}
	final[i] = NULL;
	return (final);
}
