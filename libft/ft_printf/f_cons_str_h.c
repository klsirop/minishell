/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cons_str_h.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klsirop <klsirop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:19:30 by volyvar-          #+#    #+#             */
/*   Updated: 2020/08/01 17:58:09 by klsirop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_put_plus_f(t_flags *param, int l, int *val, char **str)
{
	if (ft_strchr(param->flags, '0'))
	{
		ft_fill_symb(*str, *val, '0');
		if (((*str)[0] == '0') && ((*str)[1] != '.') && ((*str)[1] != '\0'))
		{
			(*str)[0] = '+';
		}
		else
		{
			if (ft_check_way(str, val, l, 1) == 1)
				if (ft_append_symb(str, val, l, '+') == -1)
					return (-1);
		}
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

int		ft_put_no_plus_f(t_flags *param, int l, int *val, char **str)
{
	int minus;

	minus = ft_find_min_f(*str, 1, *val);
	if ((param->flags) && (ft_strchr(param->flags, ' ')) && (minus == 0))
	{
		if (l < *val)
			(*str)[0] = ' ';
		else if (ft_plus_symb(str, ' ', val) == -1)
			return (-1);
	}
	if ((param->flags != NULL) && (ft_strchr(param->flags, '0') != NULL))
		ft_fill_symb_0_f(*str, *val, minus);
	ft_fill_symb(*str, *val, ' ');
	return (0);
}

int		ft_puttostr_f(t_flags *param, int l, int *val, char **str)
{
	int minus;

	minus = ft_find_min_f(*str, 0, *val);
	if ((param->flags != NULL) && (ft_strchr(param->flags, '-') != NULL))
	{
		if (ft_put_min_f(param, l, val, str) == -1)
			return (-1);
	}
	else
	{
		ft_new_norm_f(*str, *val, l);
		if ((param->flags) && (ft_strchr(param->flags, '+')) && (minus == 0))
		{
			if (ft_put_plus_f(param, l, val, str) == -1)
				return (-1);
		}
		else if (ft_put_no_plus_f(param, l, val, str) == -1)
			return (-1);
	}
	return (0);
}

int		ft_diff_hh(char **ta_samaya, char **str)
{
	char *tmp;

	if (ft_strlen(*ta_samaya) > ft_strlen(*str))
	{
		if (!(tmp = ft_sum(*ta_samaya, *str)))
			return (-1);
	}
	else if (!(tmp = ft_sum(*str, *ta_samaya)))
		return (-1);
	ft_strdel(ta_samaya);
	if (!(*ta_samaya = ft_strdup(tmp)))
		return (-1);
	ft_strdel(&tmp);
	return (0);
}
