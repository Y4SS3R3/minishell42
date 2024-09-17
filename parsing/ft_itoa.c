/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:53:53 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/17 16:41:12 by mzouine          ###   ########.fr       */
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

char	*ft_itoa_mz(int n, t_shell *data)
{
	int		len;
	char	*str;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup_mz("-2147483648", data));
	sign = 0;
	len = mz_int_counter(n);
	str = which_malloc(LOOP, len + 1, data);
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
