/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nan.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 13:17:40 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:32 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_start_f_h(char *s, int *l, int *val, t_flags *param)
{
	(*l) = ft_strlen(s);
	*val = *l;
	if (param->wid > *l)
		(*val) += (param->wid - *l);
	if (*val < param->pres)
		(*val) += param->pres - *val;
	return (*val);
}

void	ft_help_minus_f(int l, char *s, char **str, int i)
{
	int	j;

	j = 0;
	while (l)
	{
		(*str)[i++] = s[j];
		j++;
		l--;
	}
}

int		ft_start_f_hh(char **s, char **str, int *i)
{
	char *s1;

	if (!(s1 = ft_strdup(*s + 1)))
		return (-1);
	ft_strdel(s);
	if (!(*s = ft_strdup(s1)))
		return (-1);
	ft_strdel(&s1);
	(*str)[(*i)++] = '-';
	return (0);
}

int		ft_start_f(char **str, t_flags *param, int *l, char **s)
{
	int		val;
	int		i;
	int		pres;
	int		len;

	len = ft_strlen(*s);
	if (ft_find_a(*s, 'n', len))
		param->pres = 0;
	val = ft_start_f_h(*s, l, &val, param);
	if (!(*str = ft_strnew((size_t)(val + 1))))
		return (-1);
	i = 0;
	pres = param->pres;
	if (ft_find_a(*s, '-', len))
	{
		if (ft_start_f_hh(s, str, &i) == -1)
			return (-1);
	}
	while ((!(ft_find_a(*s, 'n', len)) && (pres-- > *l)))
		(*str)[i++] = '0';
	ft_help_minus_f(*l, *s, str, i);
	return (val);
}
