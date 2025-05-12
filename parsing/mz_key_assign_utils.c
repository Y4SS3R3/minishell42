
#include "../minishell.h"

static int	mz_valid(char c, int *flag)
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

static int	mz_next_word(t_info *info, char *s, char *key)
{
	int	n;
	int	flag;

	flag = 0;
	n = 0;
	info->i++;
	while (s[info->i] && mz_valid(s[info->i], &flag) == 1)
		info->final[info->j++] = s[info->i++];
	while (key[n])
		info->final[info->j++] = key[n++];
	return (info->j);
}

static int	mz_next_q(t_info *info, char *s, char *key, int flag)
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
		return (mz_next_word(info, s, key));
	}
	else if (flag == 2)
	{
		while (key[i])
			info->final[info->j++] = key[i++];
		return (mz_next_word(info, s, key));
	}
	else
		return (-1);
}

void	mz_key_insert(t_info *info, char *s, char *key, char *key_half)
{
	int	flag;

	info->i = 0;
	info->j = 0;
	flag = 0;
	while (s[info->i])
	{
		flag = mz_flag(s[info->i], flag);
		if (s[info->i] == '$')
		{
			if (s[info->i + 1] == '\"' || s[info->i + 1] == '\'')
				info->j = mz_next_q(info, s, key, 1);
			else if (flag == 0)
				info->j = mz_next_q(info, s, key_half, flag);
			else
				info->j = mz_next_q(info, s, key, flag);
		}
		else
			info->final[info->j++] = s[info->i++];
	}
	info->final[info->j] = '\0';
}
