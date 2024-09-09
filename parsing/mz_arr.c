/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_arr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:01:28 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/09 17:54:46 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static char	**freemem(char **final)
// {
// 	int	i;

// 	i = 0;
// 	if (final)
// 	{
// 		while (final[i])
// 		{
// 			free(final[i]);
// 			i++;
// 		}
// 		free(final);
// 	}
// 	return (NULL);
// }

static int	mz_arr_counter(char **org)
{
	int	i;
	int	n;

	if (org == NULL)
		return (0);
	i = 0;
	n = 0;
	while (org[i])
		i++;
	return (i);
}

static char	**mz_addstring(char **org, char *s, int size, t_shell *data)
{
	char	**new;
	int		i;

	i = 0;
	new = which_malloc(LOOP, (size + 1 + 1) * sizeof(char *), data);
	if (!new)
		return (NULL);
	while (i < size)
	{
		new[i] = org[i];
		i++;
	}
	new[i] = s;
	new[i + 1] = NULL;
	return (new);
}

static char	**mz_addarray(char **org, char **arr, int size, t_shell *data)
{
	char	**new;
	int		size_2;
	int		i;

	i = 0;
	size_2 = mz_arr_counter(arr);
	new = which_malloc(LOOP, (size + size_2 + 1) * sizeof(char *), data);
	while (i < size)
	{
		new[i] = org[i];
		i++;
	}
	while (i < size + size_2)
	{
		new[i] = arr[i - size];
		i++;
	}
	new[i] = NULL;
	return (new);
}

static char	**ym_addstring(char **org, char *s, int size)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc((size + 1 + 1) * sizeof(char *), 1);
	if (!new)
		return (NULL);
	if (org == NULL)
	{
		new[i++] = s;
		new[i] = NULL;
		return (new);
	}
	new[i++] = s;
	while (org[j])
	{
		new[i] = org[j];
		j++;
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**mz_arr(char **org, char **arr, char *s, int flag, t_shell *data)
{
	if (flag == 1)
		return (mz_addstring(org, s, mz_arr_counter(org), data));
	else if (flag == 2)
		return (mz_addarray(org, arr, mz_arr_counter(org), data));
	else if (flag == 3)
		return (ym_addstring(org, s, mz_arr_counter(org)));
	else
	{
		printf("Error!\n mz_arr called with wrong flag!\n");
		return (NULL);
	}
}
