/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 14:06:51 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/21 15:31:52 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_fill(long long int *num, int dig)
{
	*num += dig;
	if ((*num * 10) / 10 == *num)
		*num *= 10;
	else
	{
		*num = -10;
		return (0);
	}
	return (1);
}

int				ft_atoi(const char *str)
{
	int				sg;
	long long int	num;

	sg = 1;
	num = 0;
	while (ft_isspace(*str) && *str != '\0')
		str++;
	if (*str == '-')
		sg = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		if (!ft_fill(&num, *str - '0'))
		{
			if (sg < 0)
				num = 0;
			break ;
		}
		str++;
	}
	num /= 10;
	return (num * sg);
}
