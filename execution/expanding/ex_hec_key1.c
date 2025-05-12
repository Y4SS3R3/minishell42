
#include "../../minishell.h"

int	ex_mz_valid(char c, int *flag)
{
	if (c == '_' || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	if (c == '?' && *flag == 0)
	{
		*flag = 1;
		return (1);
	}
	return (0);
}

int	ex_mz_next_word(t_info *info, char *s, char *key)
{
	int	n;
	int	flag;

	flag = 0;
	n = 0;
	info->i++;
	while (s[info->i] && ex_mz_valid(s[info->i], &flag) == 1)
		info->final[info->j++] = s[info->i++];
	while (key[n])
		info->final[info->j++] = key[n++];
	return (info->j);
}

int	ex_mz_next_q(t_info *info, char *s, char *key, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		info->final[info->j] = '$';
		info->i++;
		return (info->j + 1);
	}
	else if (flag == 0)
	{
		while (key[i])
			info->final[info->j++] = key[i++];
		return (ex_mz_next_word(info, s, key));
	}
	else if (flag == 2)
	{
		while (key[i])
			info->final[info->j++] = key[i++];
		return (ex_mz_next_word(info, s, key));
	}
	else
		return (-1);
}

void	ex_mz_key_insert(t_info *info, char *s, char *key)
{
	info->i = 0;
	info->j = 0;
	while (s[info->i])
	{
		if (s[info->i] == '$')
			info->j = ex_mz_next_q(info, s, key, 0);
		else
			info->final[info->j++] = s[info->i++];
	}
	info->final[info->j] = '\0';
}

int	ex_mz_size_count(char *s, char *key_s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$')
			j++;
		i++;
	}
	j = j * (ft_strlen(key_s) + 1) * 2;
	j = j + ft_strlen(s) + 1;
	return (j);
}
