
#include "../../minishell.h"

static int	invalid_1(char *input, int i)
{
	if (!ft_isalpha(input[i])
		&& input[i] != '_' && input[i] != '\\' && input[i] != '$')
	{
		putstr_fd("starshell: export: `", 2);
		putstr_fd(input, 2);
		putstr_fd("': not a valid identifier\n", 2);
		return (-1);
	}
	return (0);
}

int	skip_var_name(char *input)
{
	int	i;
	int	ret;

	i = 0;
	while (input[i] && input[i] != '='
		&& !(input[i] != '\'' && input[i] != '\"'))
		i++;
	ret = invalid_1(input, i);
	if (ret)
		return (ret);
	return (i);
}

char	*export_get_name(int len, int k, char *input, t_shell *data)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = which_malloc(GLOBAL, len + 1, data);
	while (j < len)
	{
		if (input[k] == '\\')
		{
			k++;
			if (j < len)
				tmp[j] = input[k];
		}
		else
			tmp[j] = input[k];
		k++;
		j++;
	}
	tmp[j] = 0;
	return (tmp);
}

int	export_parse_name(char *tmp)
{
	int	j;

	j = 0;
	while (tmp[j])
	{
		if (!ft_isalnum(tmp[j]) && tmp[j] != '_' && tmp[j] != '+')
		{
			putstr_fd("starshell: export: `", 2);
			putstr_fd(tmp, 2);
			putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		j++;
	}
	return (0);
}

int	check_get_len(char *input, int *i, char **val, t_shell *data)
{
	int	len;

	len = 0;
	if (!input[*i])
	{
		data->add_equal = 0;
		return (-1);
	}
	(*i)++;
	if (!input[*i])
	{
		*val = "";
		return (-1);
	}
	while (input[*i])
	{
		(*i)++;
		len++;
	}
	return (len);
}
