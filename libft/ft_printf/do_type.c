/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 19:11:01 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:20:40 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_t1(char *fmt, t_flags *param)
{
	int f;

	f = 0;
	if (*fmt == 'd' || *fmt == 'i' || *fmt == 'D')
	{
		if (*fmt == 'D')
		{
			free(param->size);
			param->size = ft_strdup("l");
		}
		param->type = 0;
		f = 1;
	}
	else if (*fmt == 'X')
	{
		param->type = 4;
		f = 1;
	}
	else if (*fmt == 'x')
	{
		f = 1;
		param->type = 3;
	}
	return (f);
}

int		ft_t4(char *fmt, t_flags *param)
{
	int f;

	f = 0;
	if (*fmt == 'o' || *fmt == 'O')
	{
		if (*fmt == 'O')
		{
			free(param->size);
			param->size = ft_strdup("l");
		}
		param->type = 1;
		f = 1;
	}
	else if (*fmt == 'c' || *fmt == 'C')
	{
		if (*fmt == 'C')
		{
			free(param->size);
			param->size = ft_strdup("l");
		}
		param->type = 6;
		f = 1;
	}
	return (f);
}

int		ft_t2(char *fmt, t_flags *param)
{
	int f;

	f = 0;
	if (*fmt == 'u' || *fmt == 'U')
	{
		if (*fmt == 'U')
		{
			free(param->size);
			param->size = ft_strdup("l");
		}
		param->type = 2;
		f = 1;
	}
	else if (*fmt == 'f')
	{
		if (param->pres == -1)
			param->pres = 6;
		param->type = 5;
		f = 1;
	}
	return (f);
}

int		ft_t3(char *fmt, t_flags *param)
{
	int f;

	f = 0;
	if (*fmt == 's' || *fmt == 'S')
	{
		if (*fmt == 'S')
		{
			free(param->size);
			param->size = ft_strdup("l");
		}
		param->type = 7;
		f = 1;
	}
	else if (*fmt == 'p')
	{
		param->type = 8;
		f = 1;
	}
	else if (*fmt == '%')
	{
		param->type = 10;
		f = 1;
	}
	return (f);
}

char	*ft_type(char *fmt, t_flags *param)
{
	if (ft_t1(fmt, param))
		return (fmt + 1);
	else if (ft_t2(fmt, param))
		return (fmt + 1);
	else if (ft_t3(fmt, param))
		return (fmt + 1);
	else if (ft_t4(fmt, param))
		return (fmt + 1);
	return (fmt);
}
