
#include "../../minishell.h"

static int	are_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	is_nflag(char *str)
{
	if (str && *str == '-' && str[1] != 0 && are_n(&str[1]))
		return (1);
	return (0);
}

int	echo(int ac, char **av)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (ac >= 1)
	{
		while (is_nflag(av[i]))
		{
			i++;
			flag = 1;
		}
		while (av[i])
		{
			putstr_fd(av[i], 1);
			if (av[i + 1])
				putstr_fd(" ", 1);
			i++;
		}
	}
	if (flag == 0)
		putstr_fd("\n", 1);
	return (0);
}
