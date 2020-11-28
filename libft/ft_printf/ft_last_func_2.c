/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_func_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 18:51:55 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:21:29 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_last_func(char **mant, t_flags *param, int len)
{
	char	*str;
	int		val;

	if (!(str = ft_strdup(*mant)))
		return (-1);
	ft_strdel(mant);
	len = ft_strlen(str);
	val = ft_start_f(mant, param, &len, &str);
	if (val == -1)
		return (-1);
	ft_strdel(&str);
	if (ft_puttostr(param, len, &val, mant) == -1)
		return (-1);
	len = ft_strlen(*mant);
	ft_putstr(*mant);
	ft_strdel(mant);
	return (len);
}
