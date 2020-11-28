/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_wid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 12:22:25 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:21:07 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_f_wid(char **mant, int wid)
{
	int		len;
	char	*kek;
	char	*tmp;

	len = ft_strlen(*mant);
	if (len >= wid)
		return (len);
	if (!(kek = (char *)malloc(sizeof(char) * (wid - len + 1))))
		return (-1);
	ft_kek(&kek, ' ', wid - len);
	if (!(tmp = ft_strjoin(*mant, kek)))
		return (-1);
	ft_strdel(mant);
	ft_strdel(&kek);
	if (!(*mant = ft_strdup(tmp)))
		return (-1);
	ft_strdel(&tmp);
	return (len);
}

/*
** print a symbol to each free field
*/

void	ft_fill_symb_f(char *str, int val, char c)
{
	int i;

	i = 0;
	while (i < val)
	{
		if (str[i] == '\0')
			str[i] = c;
		i++;
	}
}

/*
** fill 0 with - or without
*/

void	ft_fill_symb_0_f(char *str, int val, int minus)
{
	int i;

	if (minus == 1)
	{
		i = 0;
		while (str[i] != '-')
			i++;
		str[i] = '0';
		str[0] = '-';
	}
	ft_fill_symb_f(str, val, '0');
}
