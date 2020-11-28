/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cons_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klsirop <klsirop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 14:05:26 by volyvar-          #+#    #+#             */
/*   Updated: 2020/08/01 17:57:36 by klsirop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_way_0_f(char *str)
{
	int minus;
	int i;

	minus = 0;
	i = 0;
	while (str && (str[i] != '\0'))
	{
		if (str[i] == '-')
			minus = 1;
		i++;
	}
	return (minus);
}

int		ft_way_1_f(char *str, int val)
{
	int minus;

	minus = 0;
	while (str && (str[val - 1] != '\0'))
	{
		if (str[val - 1] == '-')
			minus = 1;
		val--;
	}
	return (minus);
}

int		ft_find_min_f(char *str, int way, int val)
{
	if (way == 0)
		return (ft_way_0_f(str));
	else
		return (ft_way_1_f(str, val));
}

int		ft_put_min_f(t_flags *param, int l, int *val, char **str)
{
	int minus;

	minus = ft_find_min_f(*str, 0, *val);
	if ((ft_strchr(param->flags, '+') != NULL) && (minus == 0))
	{
		if (ft_check_way(str, val, l, 0) == 1)
			if (ft_append_symb(str, val, l, '+') == -1)
				return (-1);
	}
	if ((ft_strchr(param->flags, ' ') != NULL) && (minus == 0))
	{
		if (ft_check_way(str, val, l, 0) == 1)
			if (ft_append_symb(str, val, l, ' ') == -1)
				return (-1);
	}
	ft_fill_symb(*str, *val, ' ');
	return (0);
}

void	ft_new_norm_f(char *str, int val, int l)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			break ;
		}
		i++;
	}
	ft_help_new_norm(l, &str, i, val);
}
