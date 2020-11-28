/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_hhh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 21:33:55 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:21:15 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_con_h_2(int s, char **mant, t_flags *param)
{
	char	*tmp;
	int		len;
	int		n;

	if (s < 0)
	{
		if (!(tmp = ft_strjoin("-", *mant)))
			return (0);
		ft_strdel(mant);
		if (!(*mant = ft_strdup(tmp)))
			return (0);
		ft_strdel(&tmp);
	}
	if (ft_f_pres(mant, param) == -1)
		return (0);
	len = ft_f_wid(mant, param->wid);
	if (len == -1)
		return (0);
	n = ft_strlen(*mant);
	if (ft_puttostr_f(param, len, &n, mant) == -1)
		return (0);
	ft_putstr(*mant);
	len = ft_strlen(*mant);
	ft_strdel(mant);
	return (len);
}

int		f_con_h_1(char **mant, int e, int n)
{
	if (n - e >= 0)
	{
		if (ft_mult(mant, n - e, 5) == -1)
			return (-1);
		if (ft_dv(mant) == -1)
			return (-1);
		if (ft_mv_point(mant, n - e) == -1)
			return (-1);
	}
	else
	{
		if (ft_mult(mant, e - n, 2) == -1)
			return (-1);
		if (ft_dv(mant) == -1)
			return (-1);
	}
	return (0);
}

int		ft_cons_h_3(int exp, char **mant)
{
	int len;

	if (exp == -1)
		return (-1);
	if (exp == 1)
	{
		ft_putstr(*mant);
		len = ft_strlen((const char *)mant);
		ft_strdel(mant);
		return (len);
	}
	return (-3);
}

char	*ft_equal(char *ost, char *str, char **tmp)
{
	int lo;
	int ls;
	int len;

	lo = ft_strlen(ost);
	ls = ft_strlen(str);
	if (lo > ls)
		len = lo - ls;
	else
	{
		len = ls - lo;
	}
	ft_kek(tmp, '0', len);
	return (ft_equal_h(tmp, str, ost));
}

int		ft_mult_hh(char **mant, char **tmp, char **tmp1)
{
	ft_strdel(mant);
	if (!(*mant = ft_strjoin(*tmp1, *tmp)))
		return (-1);
	ft_strdel(tmp);
	ft_strdel(tmp1);
	return (0);
}
