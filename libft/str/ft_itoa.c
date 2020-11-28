/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:15:01 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/19 16:16:25 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= (-1);
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_min(void)
{
	char	*tmp;

	tmp = (char*)malloc(sizeof(char) * 12);
	tmp[0] = '-';
	tmp[1] = '2';
	tmp[2] = '1';
	tmp[3] = '4';
	tmp[4] = '7';
	tmp[5] = '4';
	tmp[6] = '8';
	tmp[7] = '3';
	tmp[8] = '6';
	tmp[9] = '4';
	tmp[10] = '8';
	tmp[11] = '\0';
	return (tmp);
}

char		*ft_itoa(int n)
{
	char	*tmp;
	int		len;

	len = ft_size(n) + 1;
	if (!(tmp = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	if (n == -2147483648)
		return (ft_min());
	if (n < 0)
	{
		tmp[0] = '-';
		n *= (-1);
	}
	if (n == 0)
		tmp[0] = '0';
	tmp[--len] = '\0';
	while (--len >= 0 && n > 0)
	{
		tmp[len] = n % 10 + '0';
		n /= 10;
	}
	return (tmp);
}
