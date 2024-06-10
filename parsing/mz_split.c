/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:39:42 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 11:36:54 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned int	mz_word_count(const char *s, char c)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			j++;
		while (s[i] != c && s[i])
			i++;
	}
	return (j);
}

static char	*mz_word_finder(const char *s, char c, int *word)
{
	int		i;
	int		j;
	char	*str;

	while (s[*word] && s[*word] == c)
		(*word)++;
	i = *word;
	while (s[*word] && s[*word] != c)
		(*word)++;
	str = ft_calloc((*word - i) + 1, 1);
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

char	**mz_split(char const *s, char c)
{
	char			**final;
	unsigned int	i;
	int				word;

	if (!s)
		return (NULL);
	word = 0;
	i = 0;
	final = ft_calloc((mz_word_count(s, c) + 1) * sizeof(char *), 1);
	if (!final)
		return (NULL);
	while (i < mz_word_count(s, c))
	{
		final[i] = mz_word_finder(s, c, &word);
		if (!final[i])
			return (freemem(final));
		i++;
		word++;
	}
	final[i] = NULL;
	return (final);
}
