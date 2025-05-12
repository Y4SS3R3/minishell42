
#include "../minishell.h"

static int	mz_flag2(char c, int flag)
{
	if (c == '\'' && flag == 0)
		return (1);
	else if (c == '\'' && flag == 1)
		return (0);
	else if (c == '\"' && flag == 0)
		return (2);
	else if (c == '\"' && flag == 2)
		return (0);
	else
		return (flag);
}

static int	mz_is_forb(char *s, int n, int i)
{
	if (i == 1)
	{
		if (s[n] == '|' || s[n] == ')' || s[n] == '&' || s[n] == '\0')
			return (1);
	}
	else if (i == 2)
	{
		if ((s[n] == '|' || s[n] == ')' || s[n] == '\0')
			|| (s[n] == '&' && s[n + 1] == '&'))
			return (0);
		else
			return (1);
	}
	return (0);
}

static int	check_after_cpar(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		flag = mz_flag2(s[i], flag);
		if (flag == 0 && s[i] == ')')
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (s[i] == '\0')
				return (0);
			if (mz_is_forb(s, i, 2) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

static int	check_after_special(char *s)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (s[i])
	{
		flag = mz_flag2(s[i], flag);
		if (flag == 0 && ((s[i] == '|') || (s[i] == '&' && s[i + 1] == '&')))
		{
			i++;
			if (s[i] == '|' || s[i] == '&')
				i++;
			while (s[i] == ' ')
				i++;
			if (s[i] == '\0')
				return (0);
			if (mz_is_forb(s, i, 1) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	mz_syntax_err(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		flag = mz_flag2(s[i], flag);
		i++;
	}
	if (flag != 0)
	{
		putstr_fd("starshell: syntax error\n", 2);
		return (1);
	}
	if (check_after_special(s) == 1 || check_after_cpar(s) == 1
		|| check_before_opar(s) == 1 || check_before_special(s) == 1)
	{
		putstr_fd("starshell: syntax error\n", 2);
		return (1);
	}
	return (0);
}
