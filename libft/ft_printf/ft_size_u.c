/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:27:44 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:12 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_h_ns_u(unsigned *num, int *l, int *val, t_flags *param)
{
	unsigned new_num;

	(*l) = 0;
	if ((*num == 0) && (param->pres != 0))
		(*l)++;
	new_num = *num;
	while (*num)
	{
		(*l)++;
		*num /= 10;
	}
	*num = new_num;
	*val = *l;
	if (param->wid > *l)
		(*val) += (param->wid - *l);
	if (*val < param->pres)
		(*val) += param->pres - *val;
	if (!(*num) && !param->pres && (param->wid == -1) && (param->flags)
		&& (ft_strchr(param->flags, '+') || ft_strchr(param->flags, ' ')))
		(*val)++;
	return (*val);
}

int		ft_ns_u(char **str, va_list *arg, t_flags *param, int *l)
{
	unsigned	num;
	int			val;
	int			i;
	int			pres;

	num = va_arg(*arg, unsigned);
	val = ft_h_ns_u(&num, l, &val, param);
	if (!(*str = ft_strnew((size_t)(val + 1))))
		return (-1);
	i = 0;
	pres = param->pres;
	while (pres-- > *l)
		(*str)[i++] = '0';
	ft_help_minus(*l, num, str, i);
	return (val);
}

int		ft_hu(unsigned char *num, int *l, int *val, t_flags *param)
{
	unsigned char new_num;

	(*l) = 0;
	if ((*num == 0) && (param->pres != 0))
		(*l)++;
	new_num = *num;
	while (*num)
	{
		(*l)++;
		*num /= 10;
	}
	*num = new_num;
	*val = *l;
	if (param->wid > *l)
		(*val) += (param->wid - *l);
	if (*val < param->pres)
		(*val) += param->pres - *val;
	if (!(*num) && !param->pres && (param->wid == -1) && (param->flags)
		&& (ft_strchr(param->flags, '+') || ft_strchr(param->flags, ' ')))
		(*val)++;
	return (*val);
}

int		ft_hh_u(char **str, va_list *arg, t_flags *param, int *l)
{
	unsigned char	num;
	int				val;
	int				i;
	int				pres;

	num = (unsigned char)va_arg(*arg, unsigned int);
	val = ft_hu(&num, l, &val, param);
	if (!(*str = ft_strnew((size_t)(val + 1))))
		return (-1);
	i = 0;
	pres = param->pres;
	while (pres-- > *l)
		(*str)[i++] = '0';
	ft_help_minus(*l, num, str, i);
	return (val);
}
