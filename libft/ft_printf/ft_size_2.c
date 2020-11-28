/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klsirop <klsirop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 10:07:18 by volyvar-          #+#    #+#             */
/*   Updated: 2020/08/01 17:56:12 by klsirop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_h_ll(long long int *num, int *l, int *val, t_flags *param)
{
	long long int new_num;

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

int		ft_ll(char **str, va_list *arg, t_flags *param, int *l)
{
	long long int	num;
	int				val;
	int				i;
	int				pres;

	num = va_arg(*arg, long long int);
	val = ft_h_ll(&num, l, &val, param);
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

int		ft_h_j(intmax_t *num, int *l, int *val, t_flags *param)
{
	intmax_t new_num;

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

int		ft_j(char **str, va_list *arg, t_flags *param, int *l)
{
	intmax_t	num;
	int			val;
	int			i;
	int			pres;

	num = va_arg(*arg, intmax_t);
	val = ft_h_j(&num, l, &val, param);
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
