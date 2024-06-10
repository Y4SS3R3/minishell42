/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:49:26 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:56:38 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"

static int	mz_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	int	i;
// 	int	flag;

// 	i = 1;
// 	flag = 0;
// 	if (ac > 1)
// 	{
// 		while (mz_strcmp(av[i], "-n"))
// 		{
// 			i++;
// 			flag = 1;
// 		}
// 		while (av[i])
// 		{
// 			printf("%s", av[i]);
// 			if (av[i + 1])
// 				printf(" ");
// 			i++;
// 		}
// 	}
// 	if (flag == 0)
// 		printf("\n");
// 	return (0);
// }
