/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 05:42:09 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:57:03 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

int	mz_is_com(char *s, int *n)
{
	char	*tmp;
	int		i;

	i = 0;
	while (s[i] != 32 && s[i])            // OR ANY OTHER SPACE SHIT !!!!
		i++;
	tmp = malloc(i + 1);
	if (!tmp)
		return (NULL);
	*n = i;
	i = 0;
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';

	return (0);
}

int	mz_checker(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while(s[i] == 32)            // OR ANY OTHER SPACE SHIT !!!!
			i++;
















	}
	return (0);
}

// int main(int ac, char **av)
// {
// 	mz_checker(av[1]);
// }
