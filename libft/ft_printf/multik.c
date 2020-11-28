/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multik.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:35:37 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:28 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_multik_h(char **str, char c)
{
	if (*str == NULL)
	{
		if (!(*str = (char *)malloc(sizeof(char) * 2)))
			return (-1);
		(*str)[0] = '5';
		(*str)[1] = '\0';
		return (0);
	}
	if (c == 'f')
	{
		ft_strdel(str);
		if (ft_new_mult(NULL) == -1)
			return (-1);
		return (0);
	}
	return (1);
}

int		ft_multik_hh(char **str, char **ost, char **tmp, char **tmp1)
{
	int lo;
	int ls;
	int len;

	if (ft_new_mult(str) == -1)
		return (-1);
	lo = ft_strlen(*ost);
	ls = ft_strlen(*str);
	if (lo > ls)
		len = lo - ls;
	else
	{
		len = ls - lo;
	}
	if (!(*tmp = (char *)malloc(sizeof(char) * (len + 1))))
		return (-1);
	if (!(*tmp1 = ft_equal(*ost, *str, tmp)))
		return (-1);
	return (0);
}

int		ft_multik_hhh(char **ost, char **str, char **tmp1)
{
	if (ft_strlen(*ost) > ft_strlen(*str))
	{
		ft_strdel(str);
		if (!(*str = ft_strdup(*tmp1)))
			return (-1);
		ft_strdel(tmp1);
	}
	else if (ft_strlen(*ost) < ft_strlen(*str))
	{
		ft_strdel(ost);
		if (!(*ost = ft_strdup(*tmp1)))
			return (-1);
		ft_strdel(tmp1);
	}
	return (0);
}

int		ft_multik_hhhh(char **tmp1, char **ost, char **str)
{
	if (!(*tmp1 = ft_sum(*ost, *str)))
		return (-1);
	ft_strdel(ost);
	if (!(*ost = ft_strdup(*tmp1)))
		return (-1);
	ft_strdel(tmp1);
	return (0);
}

int		ft_multik(char c, char **ost)
{
	static char	*str;
	char		*tmp;
	char		*tmp1;
	int			t;

	t = ft_multik_h(&str, c);
	if (t != 1)
		return (t);
	if (c == '0')
	{
		if (ft_new_mult(&str) == -1)
			return (-1);
	}
	else
	{
		if (ft_multik_hh(&str, ost, &tmp, &tmp1) == -1)
			return (-1);
		if (ft_multik_hhh(ost, &str, &tmp1) == -1)
			return (-1);
		if (ft_multik_hhhh(&tmp1, ost, &str) == -1)
			return (-1);
	}
	return (0);
}
