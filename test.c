#include "minishell.h"
#include <string.h>

char	*remove_charindex(char *src, int i1, int i2)
{
	int		len;
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	len = strlen(src) - 1;
	ret = malloc(len);
	while (src[i] && j < len)
	{
		if (i == i1 || i == i2)
			i++;
		else
		{
			ret[j] = src[i];
			j++;
			i++;
		}
	}
	ret[j] = 0;
	return (ret);
}

char	*remove_quotes_s(char *input)
{
	int	len;
	int	i;
	int	rem1;
	int	rem2;
	int	switch_f;

	len = strlen(input);
	i = 0;
	rem1 = -1;
	rem2 = -1;
	while (input[i])
	{
		switch_f = 0;
		len = strlen(input);
		if (input[i] == '"' || input[i] == '\'')
		{
			if (input[i] == '"')
				switch_f = '"';
			else
				switch_f = '\'';
			rem1 = i;
			i++;
			while (input[i])
			{
				if (input[i] == switch_f)
				{
					rem2 = i;
					input = remove_charindex(input, rem1, rem2);
					if (input == NULL)
						return (NULL);
					i = i - 2;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	return (input);
}

int main(int ac, char **av)
{
	char *rl;
	if (ac != 2)
		return (2);
	while (1)
	{
		rl = readline(">> ");
		if (!rl || *rl == ' ')
			break ;
		dprintf(2, "Ret : [%s]\n", remove_quotes_s(rl));
	}
}
