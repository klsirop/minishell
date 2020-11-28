/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:52:44 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:21:10 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_find_ind(char *str)
{
	int l;

	l = ft_strlen(str) - 1;
	while (str[l] != '1')
	{
		l--;
	}
	return (l + 1);
}

void	ft_mult_h(char **mant, int base, int *des)
{
	int i;
	int a;

	i = ft_strlen(*mant) - 1;
	while (i >= 0)
	{
		if ((*mant)[i] != '.')
		{
			a = ((*mant)[i] - '0') * base + *des;
			(*mant)[i] = a % 2 + '0';
			*des = a / 2;
		}
		i--;
	}
}

int		ft_mult(char **mant, int n, int base)
{
	int		des;
	char	*tmp;
	char	*tmp1;
	int		j;

	if (n == 0)
		return (0);
	j = 0;
	while (j < n)
	{
		des = 0;
		ft_mult_h(mant, base, &des);
		if (des != 0)
		{
			if (!(tmp = ft_strdup(*mant)))
				return (-1);
			if (!(tmp1 = ft_itoa_base(des, 2)))
				return (-1);
			if (ft_mult_hh(mant, &tmp, &tmp1) == -1)
				return (-1);
		}
		j++;
	}
	return (0);
}

int		ft_mv_point_h(char **mant, int n)
{
	char *kek;
	char *tmp;

	if (n != 0)
	{
		if (!(kek = (char *)malloc(sizeof(char) * (n + 1))))
			return (-1);
		ft_kek(&kek, '0', n);
		if (!(tmp = ft_strjoin(kek, *mant + 1)))
			return (-1);
		ft_strdel(&kek);
		ft_strdel(mant);
		if (!(*mant = ft_strdup(tmp)))
			return (-1);
		ft_strdel(&tmp);
		if (!(tmp = ft_strjoin("0.", *mant)))
			return (-1);
		ft_strdel(mant);
		if (!(*mant = ft_strdup(tmp)))
			return (-1);
		ft_strdel(&tmp);
		return (0);
	}
	return (1);
}

int		ft_mv_point(char **mant, int n)
{
	int		i;
	int		mv;

	i = 0;
	mv = 1;
	while ((*mant)[i] != '.')
		i++;
	while ((n > 0) && (i > 0))
	{
		(*mant)[i] = (*mant)[i - 1];
		i--;
		n--;
	}
	if ((mv == ft_mv_point_h(mant, n)) != 1)
		return (mv);
	(*mant)[i] = '.';
	if (ft_mv_hh(mant, i) == -1)
		return (-1);
	return (0);
}
