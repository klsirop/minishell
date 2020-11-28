/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 10:10:24 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:21:49 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_h_z(ssize_t *num, int *l, int *val, t_flags *param)
{
	ssize_t new_num;

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

int		ft_z(char **str, va_list *arg, t_flags *param, int *l)
{
	ssize_t		num;
	int			val;
	int			i;
	int			pres;

	num = va_arg(*arg, ssize_t);
	val = ft_h_z(&num, l, &val, param);
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

int		ft_h_lll(__int64_t *num, int *l, int *val, t_flags *param)
{
	__int64_t new_num;

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

int		ft_lll(char **str, va_list *arg, t_flags *param, int *l)
{
	__int64_t		num;
	int				val;
	int				i;
	int				pres;

	num = va_arg(*arg, __int64_t);
	val = ft_h_lll(&num, l, &val, param);
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
