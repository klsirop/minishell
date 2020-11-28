/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 10:19:32 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:17 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_h_norm_size(int *num, int *l, int *val, t_flags *param)
{
	int new_num;

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

int		ft_n_size(char **str, va_list *arg, t_flags *param, int *l)
{
	int num;
	int val;
	int i;
	int pres;

	num = va_arg(*arg, int);
	val = ft_h_norm_size(&num, l, &val, param);
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
	{
		(*str)[i++] = '0';
	}
	if (num < 0)
		ft_help_minus((*l)++, (long int)(num) * (-1), str, i);
	else
		ft_help_minus(*l, num, str, i);
	return (val);
}

int		ft_h_hh(signed char *num, int *l, int *val, t_flags *param)
{
	signed char new_num;

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

int		ft_hh(char **str, va_list *arg, t_flags *param, int *l)
{
	signed char	num;
	int			val;
	int			i;
	int			pres;

	num = (signed char)va_arg(*arg, int);
	val = ft_h_hh(&num, l, &val, param);
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
