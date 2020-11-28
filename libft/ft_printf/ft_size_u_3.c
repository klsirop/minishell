/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_u_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 10:38:11 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:03 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_h_z_u(size_t *num, int *l, int *val, t_flags *param)
{
	size_t	new_num;

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

int		ft_z_u(char **str, va_list *arg, t_flags *param, int *l)
{
	size_t		num;
	int			val;
	int			i;
	int			pres;

	num = va_arg(*arg, size_t);
	val = ft_h_z_u(&num, l, &val, param);
	if (!(*str = ft_strnew((size_t)(val + 1))))
		return (-1);
	i = 0;
	pres = param->pres;
	while (pres-- > *l)
		(*str)[i++] = '0';
	ft_help_minus(*l, num, str, i);
	return (val);
}

int		ft_h_lll_u(__uint64_t *num, int *l, int *val, t_flags *param)
{
	__uint64_t	new_num;

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

int		ft_z_lll(char **str, va_list *arg, t_flags *param, int *l)
{
	__uint64_t		num;
	int				val;
	int				i;
	int				pres;

	num = va_arg(*arg, __uint64_t);
	val = ft_h_lll_u(&num, l, &val, param);
	if (!(*str = ft_strnew((size_t)(val + 1))))
		return (-1);
	i = 0;
	pres = param->pres;
	while (pres-- > *l)
		(*str)[i++] = '0';
	ft_help_minus(*l, num, str, i);
	return (val);
}
