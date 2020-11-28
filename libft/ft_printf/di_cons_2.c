/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_cons_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 09:43:28 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:19:39 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_doing(t_flags *param, int l, int *val, char **str)
{
	if (*val == -1)
	{
		ft_free_param(param);
		return (-1);
	}
	if (ft_puttostr(param, l, val, str) == -1)
		return (-1);
	ft_putstr(*str);
	ft_strdel(str);
	ft_free_param(param);
	return (0);
}

int		di_con(t_flags *param, va_list *arg)
{
	int a;

	a = di_con_standart(param, arg);
	if (a == -1)
		return (0);
	else
		return (a);
}

int		ft_doing_u(t_flags *param, int l, int *val, char **str)
{
	if (*val == -1)
	{
		ft_free_param(param);
		return (-1);
	}
	if ((param->pres == 0) && (ft_find_min(*str, param->pres, 0, *val) == -1)
		&& (param->wid == -1))
		*val = 0;
	if (ft_puttostr_u(param, l, val, str) == -1)
		return (-1);
	ft_putstr(*str);
	ft_strdel(str);
	ft_free_param(param);
	return (0);
}
