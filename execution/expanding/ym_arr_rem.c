
#include "../../minishell.h"

static char	**ym_arr_remove_first(char **array, int *size, t_shell *data)
{
	int		i;
	int		j;
	int		len;
	char	**res;

	i = 1;
	j = 0;
	len = get_length(array);
	res = which_malloc(LOOP, len * sizeof(char *), data);
	while (array[i])
	{
		res[j] = ft_strdup(array[i], LOOP, data);
		i++;
		j++;
	}
	res[j] = NULL;
	*size = get_length(res);
	return (res);
}

static char	**ym_arr_remove_last(char **array,
	int index, int *size, t_shell *data)
{
	char	**res;
	int		len;
	int		i;

	len = get_length(array);
	i = 0;
	res = which_malloc(LOOP, len * sizeof(char *), data);
	while (i < index)
	{
		res[i] = ft_strdup(array[i], LOOP, data);
		i++;
	}
	res[i] = NULL;
	*size = get_length(res);
	return (res);
}

static char	**ym_arr_remove_middle(char **array,
	int index, int *size, t_shell *data)
{
	int		i;
	int		j;
	char	**res;
	int		len;

	i = 0;
	len = get_length(array);
	res = which_malloc(LOOP, len * sizeof(char *), data);
	while (i < index)
	{
		res[i] = ft_strdup(array[i], LOOP, data);
		i++;
	}
	j = i;
	i++;
	while (array[i])
	{
		res[j] = ft_strdup(array[i], LOOP, data);
		i++;
		j++;
	}
	res[j] = NULL;
	*size = get_length(res);
	return (res);
}

char	**ym_arr_rem(char **array,
	int index, int *size, t_shell *data)
{
	int		len;

	len = get_length(array);
	if (index < 0)
		index = 0;
	if (index >= len)
		index = len - 1;
	if (index == 0)
		return (ym_arr_remove_first(array, size, data));
	else if (index == len - 1)
		return (ym_arr_remove_last(array, index, size, data));
	else
		return (ym_arr_remove_middle(array, index, size, data));
	return (NULL);
}
