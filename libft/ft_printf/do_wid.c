/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_wid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:30:31 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:20:44 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_ex(t_flags *param, int f)
{
	if (param->wid < 0 && f)
	{
		if (!param->flags)
		{
			if (!(param->flags = ft_strdup("-")))
				return (0);
		}
		else
		{
			if (!(param->flags = ft_strjoin(param->flags, "-")))
				return (0);
		}
		param->wid *= (-1);
	}
	return (1);
}

char		*ft_valid_wid(char *fmt, t_flags *param, va_list *arg)
{
	int f;

	f = 0;
	while (ft_isdigit(*fmt) || (*fmt == '*'))
	{
		if (*fmt == '*')
		{
			param->wid = va_arg(*arg, int);
			fmt++;
			f = 1;
		}
		else if (ft_isdigit(*fmt))
		{
			f = 1;
			param->wid = ft_atoi(fmt);
			while (ft_isdigit(*fmt))
				fmt++;
		}
	}
	if (!ft_ex(param, f))
		return (NULL);
	return (fmt);
}
