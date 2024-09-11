/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:07:51 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/11 21:13:31 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strchr(const char *haystack, int needle)
{
	size_t	i;

	i = 0;
	if (haystack == NULL)
		return (NULL);
	while (haystack[i])
	{
		if (haystack[i] == (char)needle)
			return ((char *)&haystack[i]);
		i++;
	}
	if (haystack[i] == (char)needle)
		return ((char *)&haystack[i]);
	return (NULL);
}

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

int	words_count(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	status_check(unsigned long long n, size_t i, char *str)
{
	if (n > LLONG_MAX / 10
		|| (n == LLONG_MAX / 10 && str[i] - '0' > LLONG_MAX % 10))
	{
		putstr_fd("exit\n", 2);
		putstr_fd("starshell: exit: ", 2);
		putstr_fd(str, 2);
		putstr_fd(": numeric argument required\n", 2);
		exit (255);
	}
}

int	ft_atoi(char *str)
{
	size_t				i;
	unsigned long long	n;
	long				s;

	i = 0;
	n = 0;
	s = 1;
	if (str == NULL)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] && str[i] == '0')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		status_check(n, i, str);
		n = n * 10 + (str[i++] - 48);
	}
	return (n * s);
}
