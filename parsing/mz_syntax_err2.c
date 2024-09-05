/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_syntax_err2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:45:10 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/05 16:24:37 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	mz_flag2(char *s, int *i, int flag)
{
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
		if (s[*i])
			(*i)++;
	}
	else if (s[*i] == '\"')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\"')
			(*i)++;
		if (s[*i])
			(*i)++;
	}
	if (s[*i] && s[*i] == '(' && flag == 0)
		return (3);
	else if (s[*i] && s[*i] == '(' && flag % 3 == 0)
		return (flag + 3);
	else if (s[*i] && s[*i] == ')' && flag % 3 == 0)
		return (flag - 3);
	else if (s[*i] && s[*i] == ')' && flag == 0)
		return (-1);
	else
		return (flag);
}

int	mz_syntax_err2(char *s)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		flag = mz_flag2(s, &i, flag);
		if (((flag == 0 || flag % 3 == 0) && (s[i] == '(' && s[i + 1] == ')'))
			|| flag < 0)
			flag = -1;
		if (flag == -1)
			break ;
		if (s[i])
			i++;
	}
	if (flag != 0)
	{
		mz_free_char(s);
		printf("starshell: syntax error\n");
		return (1);
	}
	return (0);
}

/*
'ABC'| // SE // CHECK BEFORE JOIN
(ls)'fsd' // SE // AFTER CPAR: PIPE OR AND Cpar
((')') // SE
*/



// minishell:'"'''
// =================================================================
// ==96336==ERROR: AddressSanitizer: heap-buffer-overflow

// minishell:''''''''''''''''
// =================================================================
// ==97025==ERROR: AddressSanitizer: heap-buffer-overflow


// minishell:$USER'dsfdsf'|"dsfds|dsf"
// Syntax Error! >> Not a syntax error!



// minishell:'&&'
// Syntax Error!
