/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:33:51 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:56:55 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	words_count1(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != '\t')
			&& (s[i + 1] == 0 || s[i + 1] == ' ' || s[i + 1] == '\t'))
			count++;
		i++;
	}
	return (count);
}

static void	nmr_arg_req(char *arg, t_shell *data)
{
	putstr_fd("exit\n", 2);
	putstr_fd("starshell: exit: ", 2);
	putstr_fd(arg, 2);
	putstr_fd(": numeric argument required\n", 2);
	improved_exit(255, data);
}

static void	single_args(char **av, t_shell *data)
{
	int	exit_st;
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (words_count1(av[0]) != 1)
		nmr_arg_req(av[0], data);
	while (av[0][j] && (av[0][j] == ' ' || av[0][j] == '\t'))
		j++;
	i = j;
	if (av[0][j] == '+' || av[0][j] == '-')
		j++;
	while (av[0][j] && !(av[0][j] == ' ' || av[0][j] == '\t'))
	{
		if (!(av[0][j] >= '0' && av[0][j] <= '9'))
			nmr_arg_req(av[0], data);
		j++;
	}
	exit_st = ft_atoi(&av[0][i], data);
	printf("exit\n");
	improved_exit(exit_st, data);
}

static int	multiple_args(char **av, t_shell *data)
{
	int	j;

	j = 0;
	while (av[0][j] && (av[0][j] == ' ' || av[0][j] == '\t'))
		j++;
	if (av[0][j] == '+' || av[0][j] == '-')
		j++;
	while (av[0][j])
	{
		if (!(av[0][j] >= '0' && av[0][j] <= '9'))
			nmr_arg_req(av[0], data);
		j++;
	}
	ft_atoi(av[0], data);
	putstr_fd("exit\n", 2);
	putstr_fd("starshell: exit: too many arguments\n", 2);
	return (1);
}

int	exit_cmd(int ac, char **av, t_shell *data)
{
	if (ac == 0)
	{
		printf("exit\n");
		improved_exit(data->status, data);
	}
	else if (ac == 1)
		single_args(av, data);
	else
		return (multiple_args(av, data));
	return (0);
}
