/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_joiner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:32:02 by mzouine           #+#    #+#             */
/*   Updated: 2024/08/31 21:13:44 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	mz_is_ok(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	if (c == '\"' || c == '\'')
		return (1);
	if (c == '\0')
		return (1);
	if (c == '(' || c == ')' || c == '|')
		return (1);
	return (0);
}

static int	mz_swap_qt(char *s, int i, char c)
{
	while (i > 0 && mz_is_ok(s[i - 1]) == 0)
	{
		if (i > 1 && (s[i - 1] == '&' && s[i - 2] == '&'))
			break ;
		s[i] = s[i - 1];
		s[i - 1] = c;
		i--;
	}
	i++;
	while (s[i] != c)
		i++;
	while (s[i] && mz_is_ok(s[i + 1]) == 0)
	{
		if (s[i + 1] && (s[i + 1] == '&' && s[i + 2] == '&'))
			break ;
		s[i] = s[i + 1];
		s[i + 1] = c;
		i++;
	}
	return (i + 1);
}

// static char	*mz_trimmer(char *s, int i, int j, int flag)
// {
// 	char	key;
// 	char	close;
// 	char	*final;

// 	final = malloc(ft_strlen_mz(s) + 1);
// 	while (s[i])
// 	{
// 		flag = mz_flag(s[i], flag);
// 		if ((s[i] == '\"' || s[i] == '\'')
// 			&& (s[i + 1] == '\"' || s[i + 1] == '\'') && flag == 0)
// 		{
// 			close = s[i];
// 			key = s[i + 1];
// 			i = i + 2;
// 			while (s[i])
// 			{
// 				if (s[i] == key)
// 				{
// 					if (s[i + 1] == '\'' || s[i + 1] == '\"')
// 					{
// 						key = s[i + 1];
// 						i = i + 2;
// 						continue ;
// 					}
// 					final[j++] = close;
// 					i++;
// 					break ;
// 				}
// 				else
// 					final[j++] = s[i++];
// 			}
// 		}
// 		else
// 			final[j++] = s[i++];
// 	}
// 	final[j] = '\0';
// 	return (final);
// }

char	*mz_joiner(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		flag = mz_flag(s[i], flag);
		if (flag != 0)
		{
			i = mz_swap_qt(s, i, s[i]);
			flag = 0;
		}
		else
			i++;
	}
	return (s);
}
