
#include "../../minishell.h"

int	is_a_dir(char *path)
{
	DIR	*ret;

	ret = opendir(path);
	if (ret)
	{
		putstr_fd("starshell: ", 2);
		putstr_fd(path, 2);
		putstr_fd(": is a directory\n", 2);
		closedir(ret);
		return (1);
	}
	return (0);
}

void	init_1(char **file, int *expanded, char *file_src)
{
	*expanded = 0;
	*file = file_src;
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
