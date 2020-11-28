/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 10:03:05 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:21:40 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_h_h(short int *num, int *l, int *val, t_flags *param)
{
	short int new_num;

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
	if (*num < 0)
		(*l)++;
	if (param->wid > *l)
		(*val) += (param->wid - *l);
	if (*val < param->pres)
		(*val) += param->pres - *val;
	if (*num < 0)
		(*val)++;
	if (!(*num) && !param->pres && (param->wid == -1) && (param->flags)
		&& (ft_strchr(param->flags, '+') || ft_strchr(param->flags, ' ')))
		(*val)++;
	return (*val);
}

int		ft_h(char **str, va_list *arg, t_flags *param, int *l)
{
	short int	num;
	int			val;
	int			i;
	int			pres;

	num = (short int)va_arg(*arg, int);
	val = ft_h_h(&num, l, &val, param);
	if (!(*str = ft_strnew((size_t)(val + 1))))
		return (-1);
	i = 0;
	if (num < 0)
	{
		(*str)[i++] = '-';
		(*l)--;
	}
	pres = param->pres;
	while (pres-- > *l)
		(*str)[i++] = '0';
	if (num < 0)
		ft_help_minus((*l)++, (long int)(num) * (-1), str, i);
	else
		ft_help_minus(*l, num, str, i);
	return (val);
}

int		ft_h_l(long int *num, int *l, int *val, t_flags *param)
{
	long int new_num;

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
	if (*num < 0)
		(*l)++;
	if (param->wid > *l)
		(*val) += (param->wid - *l);
	if (*val < param->pres)
		(*val) += param->pres - *val;
	if (*num < 0)
		(*val)++;
	if (!(*num) && !param->pres && (param->wid == -1) && (param->flags)
		&& (ft_strchr(param->flags, '+') || ft_strchr(param->flags, ' ')))
		(*val)++;
	return (*val);
}

int		ft_l(char **str, va_list *arg, t_flags *param, int *l)
{
	long int	num;
	int			val;
	int			i;
	int			pres;

	num = va_arg(*arg, long int);
	val = ft_h_l(&num, l, &val, param);
	if (!(*str = ft_strnew((size_t)(val + 1))))
		return (-1);
	i = 0;
	if (num < 0)
	{
		(*str)[i++] = '-';
		(*l)--;
	}
	pres = param->pres;
	while (pres-- > *l)
		(*str)[i++] = '0';
	if (num < 0)
		ft_help_minus((*l)++, (long int)(num) * (-1), str, i);
	else
		ft_help_minus(*l, num, str, i);
	return (val);
}
