/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_conservation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:06:58 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:19:42 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_cwid(t_flags *param, char c, char *str, int len)
{
	if (ft_strchr(param->flags, '-'))
	{
		ft_putchar(c);
		ft_memset(str, ' ', len);
		ft_putstr(str);
	}
	else
	{
		if (param->flags != NULL && ft_strchr(param->flags, '0'))
			ft_memset(str, '0', len);
		else
			ft_memset(str, ' ', len);
		ft_putstr(str);
		ft_putchar(c);
	}
	str[len] = '\0';
}

int		c_con(t_flags *param, va_list *arg)
{
	char	c;
	char	*str;
	int		len;

	if (param->size != NULL && !ft_strcmp(param->size, "l"))
		return (c_big(param, arg));
	c = (char)va_arg(*arg, int);
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
