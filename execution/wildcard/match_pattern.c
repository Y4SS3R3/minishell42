/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:15:22 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/29 01:01:01 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_if_matched(char *pattern, int p_i)
{
	while (pattern[p_i] != '\0')
	{
		if (pattern[p_i] != '*')
			return (0);
		p_i++;
	}
	return (1);
}

static void	increment_both(int *p_i, int *s_i)
{
	(*s_i)++;
	(*p_i)++;
}

static void	back_track(int p_afterwc, int *p_i, int *s_backtrack, int *s_i)
{
	*p_i = p_afterwc;
	*s_i = ++(*s_backtrack);
}

static int	init_vars(int *s_i, int *p_i, int *p_lastwcocc, int *s_backtrack)
{
	*s_i = 0;
	*p_i = 0;
	*p_lastwcocc = -1;
	*s_backtrack = -1;
	return (-1);
}

int	match_it(char *string, char *pattern)
{
	int	s_i;
	int	p_i;
	int	p_lastwcocc;
	int	s_backtrack;
	int	p_afterwc;

	p_afterwc = init_vars(&s_i, &p_i, &p_lastwcocc, &s_backtrack);
	while (string[s_i])
	{
		if (pattern[p_i] != '\0' && pattern[p_i] == string[s_i])
			increment_both(&p_i, &s_i);
		else if (pattern[p_i] != '\0' && pattern[p_i] == '*')
		{
			p_lastwcocc = p_i;
			s_backtrack = s_i;
			p_afterwc = ++p_i;
		}
		else if (p_lastwcocc == -1)
			return (0);
		else
			back_track(p_afterwc, &p_i, &s_backtrack, &s_i);
	}
	return (check_if_matched(pattern, p_i));
}
