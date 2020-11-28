/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:11:35 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:21:18 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_cons_h_4(int e, int m, char **tmp, char **mant)
{
	char *str;

	if ((e == 0) && (m == 0))
	{
		return (ft_line_var(tmp, mant));
	}
	if ((e == 0) && (m != 0))
	{
		if (!(str = ft_strjoin("0.", *tmp + 1)))
			return (-1);
		ft_strdel(tmp);
	}
	else
	{
		if (!(str = ft_strjoin("1.", *tmp + 1)))
			return (-1);
		ft_strdel(tmp);
	}
	if (!(*mant = ft_crop(str, ft_find_ind(str) + 2)))
		return (-1);
	ft_strdel(&str);
	return (0);
}

int		ft_cons_h_5(t_float *field, char **mant, va_list *arg)
{
	int gd;
	int len;
	int ex;

	gd = ft_get_d(arg, mant, &((*field).e), &((*field).m));
	if (gd == -1)
		return (-1);
	gd ? ((*field).s = -1)
		: ((*field).s = 1);
	(*field).n = 16383;
	ex = ft_exeption((*field).s, (*field).e, (*field).m, mant);
	if (ex == -1)
		return (-1);
	if (ex == 1)
	{
		ft_putstr(*mant);
		len = ft_strlen(*mant);
		ft_strdel(mant);
		return (len);
	}
	return (-3);
}

void	ft_cons_h_6(t_float *field, t_fl *f, va_list *arg)
{
	(*f).fl = va_arg(*arg, double);
	(*field).n = 1023;
	(*field).s = ((*f).dw >> 63) ? -1 : 1;
	(*field).e = ((*f).dw >> 52) & 0x7FF;
	(*field).m = (*field).e ? ((*f).dw & 0xFFFFFFFFFFFFF) |
		0x10000000000000 : ((*f).dw & 0xFFFFFFFFFFFFF) << 1;
}

int		ft_cons_h_7(t_float *field, char **tmp, char **mant)
{
	int exp;
	int len;

	if (!(*tmp = ft_itoa_base_large((*field).m, 2)))
		return (-1);
	exp = ft_exeption((*field).s, (*field).e, (*field).m, mant);
	if (exp != 0)
		return (exp);
	len = ft_cons_h_3(exp, mant);
	return (len);
}

int		f_con(t_flags *param, va_list *arg)
{
	t_fl		f;
	char		*mant;
	char		*tmp;
	int			len;
	t_float		field;

	mant = NULL;
	if (param && (ft_strchr(param->size, 'L')))
	{
		len = ft_cons_h_5(&field, &mant, arg);
		if (len != -3)
			return (len);
	}
	else
	{
		ft_cons_h_6(&field, &f, arg);
		len = ft_cons_h_7(&field, &tmp, &mant);
		if ((len == -1) || (len == 1))
			return (ft_last_func(&mant, param, len));
		if (ft_cons_h_4(field.e, field.m, &tmp, &mant) == -1)
			return (-1);
	}
	if (f_con_h_1(&mant, field.e, field.n) == -1)
		return (-1);
	return (ft_con_h_2(field.s, &mant, param));
}
