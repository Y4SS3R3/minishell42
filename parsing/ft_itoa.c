/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_mz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:34:20 by mzouine           #+#    #+#             */
/*   Updated: 2024/08/31 21:07:21 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	mz_int_counter(int n)
{
	int	i;
	int	counter;

	counter = 0;
	i = n;
	if (n <= 0)
	{
		counter = 1;
		i = -n;
	}
	while (i > 0)
	{
		counter++;
		i = i / 10;
	}
	return (counter);
}

char	*ft_itoa_mz(int n)
{
	int		len;
	char	*str;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup_mz("-2147483648"));
	sign = 0;
	len = mz_int_counter(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	str[len] = '\0';
	while (len > 0)
	{
		str[--len] = n % 10 + 48;
		n = n / 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
