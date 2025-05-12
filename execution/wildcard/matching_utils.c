
#include "../../minishell.h"

char	*get_entry_content(char *pattern, t_shell *data)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*ent;

	dir = opendir(".");
	ent = NULL;
	if (dir == NULL)
		return (perror("Unable to open directory"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (match_it(entry->d_name, pattern))
		{
			if (*entry->d_name != '.'
				|| (*pattern == '.' && *entry->d_name == '.'))
			{
				ent = ft_strjoin(ent, entry->d_name, LOOP, data);
				ent = ft_strjoin(ent, " ", LOOP, data);
			}
		}
	}
	closedir(dir);
	return (ent);
}

char	*remove_ws(char *str, t_shell *data)
{
	int		i;
	int		len;
	int		j;
	char	*res;

	len = 0;
	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i + len] && !(str[i + len] == ' ' || str[i + len] == '\t'))
		len++;
	res = which_malloc(LOOP, len + 1, data);
	while (j < len)
	{
		res[j] = str[i + j];
		j++;
	}
	res[len] = '\0';
	return (res);
}

static int	custom_compare(char *a, char *b)
{
	int	a_start;
	int	b_start;

	a_start = a[0] == '.' || (a[0] >= 'A' && a[0] <= 'Z');
	b_start = b[0] == '.' || (b[0] >= 'A' && b[0] <= 'Z');
	if (a_start && !b_start)
		return (-1);
	if (!a_start && b_start)
		return (1);
	return (ft_strcmp(a, b));
}

void	alpha_sort(char **arr, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (custom_compare(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
