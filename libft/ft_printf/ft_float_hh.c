/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_hh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 19:54:28 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:21:22 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_dv_ost(int ekv, char **mant, char **ost)
{
	int i;

	i = ekv + 1;
	if ((*mant)[i] == '1')
	{
		if (!(*ost = ft_strdup("5")))
			return (-1);
	}
	else if (!(*ost = ft_strdup("0")))
		return (-1);
	while ((*mant)[i] != '\0')
	{
		if (ft_multik((*mant)[i], ost) == -1)
			return (-1);
		i++;
	}
	if (ft_multik('f', NULL) == -1)
		return (-1);
	return (0);
}

int		ft_dv_ta_samaya(int ekv, char **mant, char **ta_samaya)
{
	int i;

	i = ekv - 1;
	if ((*mant)[i] == '1')
	{
		if (!(*ta_samaya = ft_strdup("1")))
			return (-1);
	}
	else if (!(*ta_samaya = ft_strdup("0")))
		return (-1);
	while (i >= 0)
	{
		if (ft_diff((*mant)[i], ta_samaya) == -1)
			return (-1);
		i--;
	}
	if (ft_diff('f', NULL) == -1)
		return (-1);
	return (0);
}

void	ft_dv_h(char **tmp, char **ost, char **mant)
{
	ft_strdel(tmp);
	ft_strdel(ost);
	ft_strdel(mant);
}

int		ft_dv(char **mant)
{
	int		ekv;
	char	*ta_samaya;
	char	*tmp;
	char	*ost;

	ekv = 0;
	ta_samaya = NULL;
	ost = NULL;
	while ((*mant)[ekv] != '.')
		ekv++;
	if (ft_dv_ost(ekv, mant, &ost) == -1)
		return (-1);
	if (ft_dv_ta_samaya(ekv, mant, &ta_samaya) == -1)
		return (-1);
	if (!(tmp = ft_strjoin(ta_samaya, ".")))
		return (-1);
	ft_strdel(&ta_samaya);
	if (!(ta_samaya = ft_strjoin(tmp, ost)))
		return (-1);
	ft_dv_h(&tmp, &ost, mant);
	if (!(*mant = ft_strdup(ta_samaya)))
		return (-1);
	ft_strdel(&ta_samaya);
	return (0);
}

int		ft_get_d(va_list *arg, char **mant, int *e, unsigned long long int *m)
{
	t_double	d;
	char		*tmp;
	char		*str;

	d.ld = va_arg(*arg, long double);
	*e = d.bytes.exponent;
	*m = d.bytes.mantisa;
	if (!(tmp = ft_itoa_base_large(d.bytes.mantisa, 2)))
		return (-1);
	if (!(str = ft_strjoin("1.", tmp + 1)))
		return (-1);
	if (!(*mant = ft_crop(str, ft_find_ind(str) + 2)))
		return (-1);
	ft_strdel(&str);
	ft_strdel(&tmp);
	return (d.bytes.sign);
}
