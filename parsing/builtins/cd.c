/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:50:32 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:56:32 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

static int	cd_error1(char *s)
{
	printf("cd: string not in pwd: %s\n", s);
	return (1);
}

static int	cd_error2(void)
{
	printf("cd: too many arguments\n");
	return (1);
}

// int	main(int ac, char **av)
// {
// 	printf("%s\n", getcwd(NULL, 0));
// 	if(ac == 1)
// 	{
// 		if (chdir(getenv("HOME")) != 0)
// 		{
// 			printf("cd: failed to cd to home directory");
// 			return (1);
// 		}
// 	}
// 	else if (ac == 3)
// 		return (cd_error1(av[1]));
// 	else if (ac > 3)
// 		return (cd_error2());
// 	else
// 	{
// 		if (chdir(av[1]) != 0)
// 		{
// 			printf("cd: no such file or directory: %s\n", av[1]);
// 			return (1);
// 		}
// 	}
// 	printf("%s\n", getcwd(NULL, 0));
// 	return (0);
// }
