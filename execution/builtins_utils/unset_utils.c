
#include "../../minishell.h"

static int	check_check(int *check, char *input)
{
	(*check)++;
	if (*check > 1)
	{
		putstr_fd("starshell: unset: `", 2);
		putstr_fd(input, 2);
		putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

static int	check_unwanted_char1(char *input, int i)
{
	if (!ft_isalnum(input[i]) && input[i] != '_'
		&& input[i] != '\\' && input[i] != '$')
	{
		putstr_fd("starshell: unset: `", 2);
		putstr_fd(input, 2);
		putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

static int	unset_parse_var(char *input, int *i)
{
	int	check;
	int	len;

	check = 0;
	len = 0;
	while (input[*i] && input[*i] != '\'' && input[*i] != '\"')
	{
		if (check_unwanted_char1(input, *i))
			return (-1);
		if (input[*i] == '\\')
		{
			if (check_check(&check, input))
				return (-1);
			(*i)++;
		}
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}

static int	check_unwanted_char(char *input)
{
	if (!ft_isalpha(input[0]) && input[0] != '_'
		&& input[0] != '\\' && input[0] != '$')
	{
		putstr_fd("starshell: unset: `", 2);
		putstr_fd(input, 2);
		putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	check_var(char *input, char **name, t_shell *data)
{
	int		i;
	int		k;
	int		len;

	i = 0;
	while (input[i] && input[i] != '='
		&& !(input[i] != '\'' && input[i] != '\"'))
		i++;
	if (check_unwanted_char(input))
		return (1);
	k = i;
	len = unset_parse_var(input, &i);
	if (len == -1)
		return (1);
	*name = export_get_name(len, k, input, data);
	return (0);
}
