#include <stdio.h>
#include <stdlib.h>

static char	**freemem(char **final)
{
	int	i;

	i = 0;
	if (final)
	{
		while (final[i])
		{
			free(final[i]);
			i++;
		}
		free(final);
	}
	return (NULL);
}

static int	mz_arr_counter(char **org)
{
	int	i;

	i = 0;
	while (org[i])
		i++;

	return (i);
}

static char	**mz_addstring(char **org, char *s, int size)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc((size + 1 + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (i < size)
	{
		new[i] = org[i];
		if (!new[i])
			return (freemem(new));
		i++;
	}
	new[i] = s;
	if (!new[i])
		return (freemem(new));
	new[i + 1] = NULL;
	return (new);
}

static char	**mz_addarray(char **org, char **arr, int size)
{
	char	**new;
	int		size_2;
	int		i;

	i = 0;
	size_2 = mz_arr_counter(arr);
	new = malloc((size + size_2 + 1) * sizeof(char *));
	while (i < size)
	{
		new[i] = org[i];
		if (!new[i])
			return (freemem(new));
		i++;
	}
	while (i < size + size_2)
	{
		new[i] = arr[i - size];
		if (!new[i])
			return (freemem(new));
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**mz_arr(char **org, char **arr, char *s, int flag) // 1 to add string, 2 to add array !
{
	if (flag == 1)
		return (mz_addstring(org, s, mz_arr_counter(org)));
	else if (flag == 2)
		return (mz_addarray(org, arr, mz_arr_counter(org)));
	else
	{
		printf("Error!\n mz_arr called with wrong flag!\n");
		return (NULL);
	}
}

void lol(void)
{
	system("leaks a.out");
}

// int main(void)
// {
// 	atexit(lol);
//     char **shesh;
//     char **shesh1;
// 	int i = 0;
// 	char **tmp;

// 	shesh = malloc(4 * sizeof(char *));
//     shesh1 = malloc(4 * sizeof(char *));

// 	shesh[0] = "Helloooo";
// 	shesh[1] = "appaaaah";
// 	shesh[2] = "niggerrr";
// 	shesh[3] = NULL;

// 	shesh1[0] = "Salaaamm";
// 	shesh1[1] = "tibariii";
// 	shesh1[2] = "zdimboumbah";
// 	shesh1[3] = NULL;
// 	printf("\n================\n\n");
// 	while (shesh[i])
// 	{
// 		printf("%s\n", shesh[i]);
// 		i++;
// 	}
// 	tmp = shesh;
// 	shesh = mz_arr(shesh, shesh1, NULL, 2);
// 	printf("\n================\n\n");
// 	i = 0;
// 	while (shesh[i])
// 	{
// 		printf("%s\n", shesh[i]);
// 		i++;
// 	}
// 	printf("\n================\n\n");
// 	free(shesh);
// 	free(shesh1);
// 	free(tmp);
//     return (0);
// }
