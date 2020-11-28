/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:53:50 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:21:33 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list		arg;
	int			val;

	val = 0;
	va_start(arg, format);
	create_func();
	ft_read_arg(&arg, (char *)format, &val);
	va_end(arg);
	return (val);
}

void	create_func(void)
{
	g_func[0] = di_con;
	g_func[1] = o_con;
	g_func[2] = u_con;
	g_func[3] = x_con;
	g_func[4] = x_up_con;
	g_func[5] = f_con;
	g_func[6] = c_con;
	g_func[7] = s_con;
	g_func[8] = p_con;
}

int		ft_percent(t_flags *param, char c)
{
	char	*str;
	int		len;

	if (param->wid > 0)
	{
		if (!(str = ft_strnew((size_t)(param->wid))))
			return (0);
		len = param->wid - 1;
	}
	else
	{
		ft_putchar(c);
		return (1);
	}
	ft_cwid(param, c, str, len);
	len = ft_strlen(str) + 1;
	return (len);
}
