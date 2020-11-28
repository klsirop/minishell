/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_func_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:53:41 by volyvar-          #+#    #+#             */
/*   Updated: 2019/09/06 13:15:45 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_way_0(char *str, int pres)
{
	int minus;
	int flag;
	int i;

	flag = -1;
	minus = 0;
	i = 0;
	while (str && (str[i] != '\0'))
	{
		if (str[i] == '-')
			minus = 1;
		if (((str[i] >= '1') && (str[i] <= '9')) || (str[i] == 'i')
			|| (str[i] == 'n') || (str[i] == 'f') ||
			(str[i] == 'a'))
			flag = 1;
		i++;
	}
	if ((pres == 0) && (flag == -1))
		return (-1);
	return (minus);
}

int		ft_way_1(char *str, int pres, int val)
{
	int minus;
	int flag;

	flag = -1;
	minus = 0;
	while (str && val >= 1 && (str[val - 1] != '\0'))
	{
		if (str[val - 1] == '-')
			minus = 1;
		if (((str[val - 1] >= '1') && (str[val - 1] <= '9')) ||
			(str[val - 1] == 'i') || (str[val - 1] == 'n') ||
			(str[val - 1] == 'f') || (str[val - 1] == 'a'))
			flag = 1;
		val--;
	}
	if ((pres == 0) && (flag == -1))
		return (-1);
	return (minus);
}

int		ft_find_min(char *str, int pres, int way, int val)
{
	if (way == 0)
		return (ft_way_0(str, pres));
	else
		return (ft_way_1(str, pres, val));
}
