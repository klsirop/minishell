/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_large.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:16:46 by jmaynard          #+#    #+#             */
/*   Updated: 2019/09/06 10:47:52 by jmaynard         ###   ########.fr       */
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

long long int	ft_atoi_large(const char *str, int *flag)
{
	long long int	sg;
	long long int	num;

	num = 0;
	while (ft_isspace(*str) && *str != '\0')
		str++;
	sg = *str == '-' ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		if (!(*flag = ft_fill(&num, *str - '0')))
		{
			num = (sg < 0) ? 0 : num;
			break ;
		}
		str++;
	}
	if (*str != '\0')
	{
		*flag = 0;
		return (num);
	}
	num /= 10;
	return (num * sg);
}
