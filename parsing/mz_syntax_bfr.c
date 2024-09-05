/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_syntax_bfr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:32:36 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/05 15:28:15 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	mz_flag2(char c, int flag)
{
	if (c == '\'' && flag == 0)
		return (1);
	else if (c == '\'' && flag == 1)
		return (0);
	else if (c == '\"' && flag == 0)
		return (2);
	else if (c == '\"' && flag == 2)
		return (0);
	else
		return (flag);
}

static int	mz_is_forb(char *s, int n, int i)
{
	if (i == 1)
	{
		if (s[n] == '|' || s[n] == '(' || s[n] == '&' || s[n] == '<' || s[n] == '>')
			return (1);
	}
	else if (i == 2)
	{
		if (s[n] == '|' || s[n] == '(')
			return (0);
		else if (n >= 1)
		{
			if (s[n] == '&' && s[n-1] == '&')
				return (0);
		}
			return (1);
	}
	return (0);
}

int check_before_opar(char *s)
{
	int i;
	int	j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	while (s[i])
	{
		flag = mz_flag2(s[i], flag);
		if (flag == 0 && s[i] == '(')
		{
			j = i;
			if (j > 0)
				j--;
			while (j > 0 && s[j] == ' ')
				j--;
			if (mz_is_forb(s, j, 2) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_before_special(char *s)
{
	int i;
	int	j;
	int flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		flag = mz_flag2(s[i], flag);
		if (flag == 0 && ((s[i] == '|') || (s[i] == '&' && s[i+1] == '&')))
		{
			j = i - 1;
			i++;
			if (s[i] == '|' || s[i] == '&')
				i++;
			while (j > 0 && s[j] == ' ')
				j--;
			if (j < 0)
				return (1);
			if (mz_is_forb(s, j, 1) == 1)
				return (1);
		}
		if (s[i])
			i++;
	}
	return (0);
}
