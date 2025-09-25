/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:01:50 by qizhang           #+#    #+#             */
/*   Updated: 2024/11/22 01:40:44 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

static char	*pre_conv(int len);
static int	int_len(long nbr);

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*res;
	long	nbr;

	nbr = n;
	len = int_len(nbr);
	res = pre_conv(len);
	if (!res)
		return (0);
	if (nbr < 0)
		nbr = -nbr;
	i = len - 1;
	while (nbr != 0)
	{
		res[i] = ((nbr % 10) + 48);
		nbr = nbr / 10;
		i --;
	}
	if (n < 0)
		res[0] = '-';
	res[len] = 0;
	return (res);
}

static char	*pre_conv(int len)
{
	char	*tmp;

	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (0);
	tmp[0] = '0';
	return (tmp);
}

static int	int_len(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count ++;
		nbr = -nbr;
	}
	if (nbr == 0)
		count ++;
	while (nbr != 0)
	{
		nbr /= 10;
		count ++;
	}
	return (count);
}
