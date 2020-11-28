/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:45:33 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:54 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_no_minus_u(char **str, t_flags *param, int l, int *val)
{
	int minus;

	minus = ft_find_min(*str, param->pres, 0, *val);
	if ((param->pres >= l) && (minus == 0))
		l = param->pres;
	if ((param->pres >= l) && (minus == 1))
		l = param->pres + 1;
	ft_new_norm(*str, *val, l, param->pres);
	{
		if ((param->pres <= 0) && (param->flags != NULL) &&
			(ft_strchr(param->flags, '0') != NULL))
		{
			if (param->pres <= -1)
				ft_fill_symb_0_f(*str, *val, minus);
			else
				ft_fill_symb_0(*str, *val, minus, param->pres - l);
		}
		if (minus != -1)
			ft_fill_symb(*str, *val, ' ');
	}
}

int		ft_puttostr_u(t_flags *param, int l, int *val, char **str)
{
	int minus;

	minus = ft_find_min(*str, param->pres, 0, *val);
	if ((param->flags != NULL) && (ft_strchr(param->flags, '-') != NULL))
	{
		if ((param->pres >= l) && (minus == 0))
			l = param->pres;
		if ((param->pres >= l) && (minus == 1))
			l = param->pres + 1;
		ft_fill_symb(*str, *val, ' ');
	}
	else
		ft_no_minus_u(str, param, l, val);
	if ((param->pres == 0) && (minus == -1))
		ft_fill_symb(*str, *val, ' ');
	return (0);
}

int		u_con_standart(t_flags *param, va_list *arg)
{
	int		val;
	char	*str;
	int		l;

	ft_di_start(&str, &val, &l);
	if (param->size == NULL)
		val = ft_ns_u(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "hh") != NULL))
		val = ft_hh_u(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "h") != NULL))
		val = ft_h_u(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "ll") != NULL))
		val = ft_ll_u(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "l") != NULL))
		val = ft_l_u(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "j") != NULL))
		val = ft_j_u(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "z") != NULL))
		val = ft_z_u(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "L") != NULL))
		val = ft_z_lll(&str, arg, param, &l);
	if (ft_doing_u(param, l, &val, &str) == -1)
		return (-1);
	return (val);
}

int		u_con(t_flags *param, va_list *arg)
{
	int a;

	a = u_con_standart(param, arg);
	if (a == -1)
		return (0);
	else
		return (a);
}
