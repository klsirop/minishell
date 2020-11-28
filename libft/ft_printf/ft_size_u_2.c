/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_u_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klsirop <klsirop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 10:35:15 by volyvar-          #+#    #+#             */
/*   Updated: 2020/08/01 17:56:40 by klsirop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_hllu(unsigned long long *num, int *l, int *val, t_flags *param)
{
	unsigned long long new_num;

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

int		ft_ll_u(char **str, va_list *arg, t_flags *param, int *l)
{
	unsigned long long	num;
	int					val;
	int					i;
	int					pres;

	num = va_arg(*arg, unsigned long long);
	val = ft_hllu(&num, l, &val, param);
	if (!(*str = ft_strnew((size_t)(val + 1))))
		return (-1);
	i = 0;
	pres = param->pres;
	while (pres-- > *l)
		(*str)[i++] = '0';
	ft_help_minus(*l, num, str, i);
	return (val);
}

int		ft_h_j_u(uintmax_t *num, int *l, int *val, t_flags *param)
{
	uintmax_t new_num;

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

int		ft_j_u(char **str, va_list *arg, t_flags *param, int *l)
{
	uintmax_t	num;
	int			val;
	int			i;
	int			pres;

	num = va_arg(*arg, uintmax_t);
	val = ft_h_j_u(&num, l, &val, param);
	if (!(*str = ft_strnew((size_t)(val + 1))))
		return (-1);
	i = 0;
	pres = param->pres;
	while (pres-- > *l)
		(*str)[i++] = '0';
	ft_help_minus(*l, num, str, i);
	return (val);
}
