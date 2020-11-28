/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_ost.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:11:17 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:20:16 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_try_put_plus(char **str, int val)
{
	int i;

	i = val - 1;
	while ((i >= 0) && ((*str)[i] != '\0'))
		i--;
	if ((i < 0) || ((i == 0) && ((*str)[i] != '\0')))
		return (0);
	if ((*str)[i] == '\0')
		(*str)[i] = '+';
	return (1);
}

void	ft_di_start(char **str, int *val, int *l)
{
	*str = NULL;
	*val = 0;
	*l = 0;
}

/*
** print a symbol to each free field
*/

void	ft_fill_symb(char *str, int val, char c)
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
