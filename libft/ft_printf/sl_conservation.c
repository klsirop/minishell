/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_conservation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:55:47 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:48 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

wchar_t		*ft_crop_w(wchar_t *str, int len)
{
	wchar_t		*tmp;
	int			i;

	i = 0;
	if (!(tmp = (wchar_t *)ft_memalloc((size_t)(len + 1))))
		return (NULL);
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	return (tmp);
}

int			ft_strlen_w(wchar_t *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str <= 0x7F)
			i++;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		str++;
	}
	return (i);
}

void		ft_putstr_w(wchar_t *str, int pres)
{
	if (pres == -1)
		pres = ft_strlen_w(str);
	while (pres > 0 && *str != '\0')
	{
		ft_putch(*str);
		str++;
		pres--;
	}
}

int			ft_wwid(t_flags *param, int len, char *tmp)
{
	int		m;

	m = 0;
	if (param->flags != NULL && ft_strchr(param->flags, '0')
		&& !ft_strchr(param->flags, '-'))
		ft_memset(tmp, '0', (size_t)(param->wid - len));
	else
		ft_memset(tmp, ' ', (size_t)(param->wid - len));
	if (ft_strchr(param->flags, '-'))
		m = 1;
	else
		m = ft_strlen(tmp);
	if (m > 1)
		ft_putstr(tmp);
	return (m);
}

int			s_big(t_flags *param, va_list *arg)
{
	wchar_t	*str;
	int		len;
	char	*tmp;
	int		m;

	str = va_arg(*arg, wchar_t *);
	m = 0;
	tmp = NULL;
	if (str == NULL)
		str = L"(null)";
	len = ft_strlen_w(str);
	if (len < param->wid)
	{
		if (!(tmp = ft_strnew((size_t)(param->wid - len + 1))))
			return (0);
		m = ft_wwid(param, len, tmp);
	}
	len = ft_strlen_w(str);
	ft_putstr_w(str, param->pres);
	m == 1 ? ft_putstr(tmp) : 0;
	m > 1 ? len += m : 0;
	ft_strdel(&tmp);
	return (len);
}
