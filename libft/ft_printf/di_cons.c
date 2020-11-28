/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_cons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 09:59:48 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:19:59 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		di_con_standart(t_flags *param, va_list *arg)
{
	int		val;
	char	*str;
	int		l;

	ft_di_start(&str, &val, &l);
	if (param->size == NULL)
		val = ft_n_size(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "hh") != NULL))
		val = ft_hh(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "h") != NULL))
		val = ft_h(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "l") != NULL))
		val = ft_l(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "ll") != NULL))
		val = ft_ll(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "j") != NULL))
		val = ft_j(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "z") != NULL))
		val = ft_z(&str, arg, param, &l);
	else if ((param->size) && (ft_strstr(param->size, "L") != NULL))
		val = ft_lll(&str, arg, param, &l);
	if (ft_doing(param, l, &val, &str) == -1)
		return (-1);
	return (val);
}

int		ft_put_min(t_flags *param, int l, int *val, char **str)
{
	int minus;

	minus = ft_find_min(*str, param->pres, 0, *val);
	if ((param->pres >= l) && (minus == 0))
		l = param->pres;
	if ((param->pres >= l) && (minus == 1))
		l = param->pres + 1;
	if ((ft_strchr(param->flags, '+') != NULL) &&
		(minus <= 0) && !(ft_find_a(*str, 'a', *val)))
	{
		if (ft_check_way(str, val, l, 0) == 1)
			if (ft_append_symb(str, val, l, '+') == -1)
				return (-1);
	}
	if ((ft_strchr(param->flags, ' ') != NULL) && (minus == 0)
		&& !(ft_find_a(*str, 'a', *val)))
	{
		if (ft_check_way(str, val, l, 0) == 1)
			if (ft_append_symb(str, val, l, ' ') == -1)
				return (-1);
	}
	ft_fill_symb(*str, *val, ' ');
	return (0);
}

int		ft_put_plus(t_flags *param, int l, int *val, char **str)
{
	int minus;

	minus = ft_find_min(*str, param->pres, 1, *val);
	if ((ft_strchr(param->flags, '0')) && (param->pres <= 0) && (minus != -1))
	{
		if (param->pres <= -1)
			ft_fill_symb_0_f(*str, *val, '0');
		else
			ft_fill_symb_0(*str, *val, minus, param->pres - l);
		if (((*str)[0] == '0') && ((*str)[1] != '\0') &&
			(param->pres <= -1) && !(ft_find_a(*str, 'a', *val)))
			(*str)[0] = '+';
		else if (ft_try_put_plus(str, *val) == 0)
			if (ft_check_way(str, val, l, 1) == 1)
				if (ft_append_symb(str, val, l, '+') == -1)
					return (-1);
	}
	else
	{
		if (ft_check_way(str, val, l, 1) == 1)
			if (ft_append_symb(str, val, l, '+') == -1)
				return (-1);
		ft_fill_symb(*str, *val, ' ');
	}
	return (0);
}

int		ft_put_no_plus(t_flags *param, int l, int *val, char **str)
{
	int minus;

	minus = ft_find_min(*str, param->pres, 1, *val);
	if ((param->flags) && (ft_strchr(param->flags, ' ')) && (minus == 0))
	{
		if (l < *val)
			(*str)[0] = ' ';
		else if (ft_plus_symb(str, ' ', val) == -1)
			return (-1);
	}
	if ((param->pres <= 0) && (param->flags != NULL) &&
		(ft_strchr(param->flags, '0') != NULL) && (minus != -1)
			&& !(ft_find_a(*str, 'a', *val)))
	{
		if (param->pres <= -1)
			ft_fill_symb_0_f(*str, *val, minus);
		else
			ft_fill_symb_0(*str, *val, minus, param->pres - l);
	}
	if (minus != -1)
	{
		ft_fill_symb(*str, *val, ' ');
	}
	return (0);
}

int		ft_puttostr(t_flags *param, int l, int *val, char **str)
{
	int minus;

	minus = ft_find_min(*str, param->pres, 0, *val);
	if ((param->flags != NULL) && (ft_strchr(param->flags, '-') != NULL))
	{
		if (ft_put_min(param, l, val, str) == -1)
			return (-1);
	}
	else
	{
		if ((param->pres >= l) && (minus != -1))
			l = param->pres + minus;
		ft_new_norm(*str, *val, l, param->pres);
		if ((param->flags) && (ft_strchr(param->flags, '+')) && (minus <= 0)
			&& !(ft_find_a(*str, 'a', *val)))
		{
			if (ft_put_plus(param, l, val, str) == -1)
				return (-1);
		}
		else if (ft_put_no_plus(param, l, val, str) == -1)
			return (-1);
	}
	ft_fill_symb(*str, *val, ' ');
	return (0);
}
