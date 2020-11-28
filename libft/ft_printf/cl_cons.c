/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_cons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 15:50:12 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:19:46 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

static int		size_wchar(unsigned int wc)
{
	if (wc <= 127)
		return (1);
	else if (wc >= 128 && wc <= 2047)
		return (2);
	else if (wc >= 2048 && wc <= 65535)
		return (3);
	else if (wc >= 65536 && wc <= 2097151)
		return (4);
	else
		return (0);
}

int				ft_putch(wchar_t wc)
{
	char					size;
	unsigned char			curr_byte;
	int						len;

	size = size_wchar(wc);
	len = 0;
	if (size == 1)
		return (ft_print_char(wc));
	curr_byte = (240 << (4 - size)) | (wc >> ((size - 1) * 6));
	len += ft_print_char(curr_byte);
	size--;
	while (size--)
	{
		curr_byte = ((wc >> ((size) * 6)) & 63) | 128;
		len += ft_print_char(curr_byte);
	}
	return (len);
}

void			ft_wcwid(t_flags *param, char c, char *str, int *len)
{
	if (param->flags != NULL && ft_strchr(param->flags, '-'))
	{
		ft_memset(str, ' ', *len);
		str[*len] = '\0';
		*len += ft_putch(c);
		ft_putstr(str);
	}
	else
	{
		if (param->flags != NULL && ft_strchr(param->flags, '0'))
			ft_memset(str, '0', *len);
		else
			ft_memset(str, ' ', *len);
		str[*len] = '\0';
		ft_putstr(str);
		*len += ft_putch(c);
	}
}

int				c_big(t_flags *param, va_list *arg)
{
	wchar_t		c;
	char		*str;
	int			len;

	c = (wchar_t)va_arg(*arg, wint_t);
	if (param->wid > 0)
	{
		if (!(str = (char *)ft_memalloc((size_t)(param->wid))))
			return (0);
		len = param->wid - size_wchar(c);
		ft_wcwid(param, c, str, &len);
		ft_strdel(&str);
	}
	else
	{
		len = ft_putch(c);
		return (len);
	}
	return (len);
}
