
#include "../../minishell.h"

char	*remove_charindex(char *src, int i1, int i2, t_shell *data)
{
	int		len;
	int		i;
	int		j;
	char	*ret;

	len = ft_strlen(src);
	ret = which_malloc(LOOP, len + 1, data);
	i = 0;
	j = 0;
	while (src[i] && j < len)
	{
		if ((i != i1 && i != i2)
			&& !((i1 > 0 && i == i1 - 1 && src[i] == '$')
				|| (i2 > 0 && i == i2 - 1 && src[i] == '$')))
		{
			ret[j] = src[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

int	get_switch_value(int c)
{
	int	switch_f;

	if (c == '"')
		switch_f = '"';
	else
		switch_f = '\'';
	return (switch_f);
}
