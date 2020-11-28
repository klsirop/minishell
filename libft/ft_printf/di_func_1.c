/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_func_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:28:40 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:20:03 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_check_way(char **str, int *val, int l, int way)
{
	if ((l == 0) && (way == 0))
	{
		(*str)[0] = '+';
		return (0);
	}
	if ((l == 0) && (way == 1))
	{
		(*str)[*val - 1] = '+';
		return (0);
	}
	return (1);
}

int		ft_fill_symb_0_h(char *str, int val, int ost_pres)
{
	int i;

	i = val - 1;
	while ((i >= 0) && (ost_pres > 0))
	{
		if (str[i] == '\0')
			str[i] = '0';
		i--;
		ost_pres--;
	}
	return (i);
}

/*
** fill 0 with - or without
*/

void	ft_fill_symb_0(char *str, int val, int minus, int ost_pres)
{
	int i;
	int ind;

	if (ost_pres > 0)
	{
		if (minus == 1)
		{
			i = 0;
			while (str[i] != '-')
				i++;
			str[i] = '0';
		}
		ost_pres--;
		ind = ft_fill_symb_0_h(str, val, ost_pres);
		str[ind] = '-';
	}
	if (ost_pres > 0)
		ind = ft_fill_symb_0_h(str, val, ost_pres);
}

void	ft_help_new_norm(int l, char **str, int i, int val)
{
	int tmp;

	i = l;
	tmp = val;
	while (l)
	{
		(*str)[tmp - 1] = (*str)[l - 1];
		l--;
		tmp--;
	}
	l = i;
	i = 0;
	while (i < val - l)
	{
		(*str)[i] = '\0';
		i++;
	}
}

void	ft_new_norm(char *str, int val, int l, int pres)
{
	int i;
	int flag_minus;

	flag_minus = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			flag_minus = 1;
			break ;
		}
		i++;
	}
	if (pres >= l)
	{
		if (flag_minus == 0)
			l = pres;
		else
			l = pres + 1;
	}
	ft_help_new_norm(l, &str, i, val);
}
