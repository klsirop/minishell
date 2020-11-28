/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_ost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:04:30 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:21:03 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_new_max(int lb, int ls)
{
	if (lb >= ls)
		return (lb);
	else
		return (ls);
}

int		ft_mv_hh(char **mant, int i)
{
	char *tmp;

	if (i == 0)
	{
		if (!(tmp = ft_strjoin("0", *mant)))
			return (-1);
		ft_strdel(mant);
		if (!(*mant = ft_strdup(tmp)))
			return (-1);
		ft_strdel(&tmp);
	}
	return (0);
}

int		ft_exeption_h(int s, int e, unsigned long long int m, char **mant)
{
	if (e == 2047)
	{
		if ((s == 1) && (m == 0x10000000000000))
		{
			ft_strdel(mant);
			if (!(*mant = ft_strdup("inf")))
				return (-1);
		}
		else if ((s == -1) && (m == 0x10000000000000))
		{
			ft_strdel(mant);
			if (!(*mant = ft_strdup("-inf")))
				return (-1);
		}
		else
		{
			ft_strdel(mant);
			if (!(*mant = ft_strdup("nan")))
				return (-1);
		}
		return (1);
	}
	return (0);
}

int		ft_exeption(int s, int e, unsigned long long int m, char **mant)
{
	int ex;

	ex = ft_exeption_h(s, e, m, mant);
	if ((ex == 1) || (ex == -1))
		return (ex);
	if ((e == 0) && (m == 0) && (s == -1))
	{
		if (mant && *mant)
			ft_strdel(mant);
		if (!(*mant = ft_strdup("-0")))
			return (-1);
		return (0);
	}
	return (0);
}
