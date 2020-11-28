/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_conservation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 18:45:42 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:40 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_prescision(t_flags *param, char **str)
{
	int		len;
	char	*tmp;
	char	*s;

	len = ft_strlen(*str);
	if (len < param->pres)
	{
		if (!(tmp = ft_strnew((size_t)(param->pres - len + 1))))
			return (-1);
		ft_memset(tmp, '0', (size_t)(param->pres - len));
		if (!(s = ft_strjoin(tmp, *str)))
			return (-1);
		ft_strdel(str);
		ft_strdel(&tmp);
		if (!(*str = ft_strdup(s)))
			return (-1);
		ft_strdel(&s);
		return (1);
	}
	return (0);
}

int		ft_put_x(char **str, int len, int flag, char *c)
{
	int		i;
	char	*tmp;

	i = 0;
	if (len == 1 && (*str)[0] == '0')
		return (1);
	len = ft_strlen(*str);
	while (i < len && ft_isalnum((*str)[len - i - 1]))
		i++;
	if (i == len)
	{
		if (!ft_eq(str, &tmp, flag, c))
			return (0);
	}
	else if (len - i >= 1)
	{
		if (!(tmp = ft_difference(str, len - i, c)))
			return (0);
	}
	else if (!(tmp = ft_strjoin(c, *str)))
		return (0);
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (1);
}

int		del(char **str)
{
	ft_strdel(str);
	return (0);
}

int		p_con(t_flags *param, va_list *arg)
{
	char	*str;
	int		len;
	int		flag;

	if (param->pres == 0)
		str = ft_strdup("");
	else
		str = ft_itoa_base_large((long long)va_arg(*arg, void *), 16);
	if (!str)
		return (0);
	if ((flag = ft_prescision(param, &str)) < 0)
		return (del(&str));
	if (!ft_width(param, &str, ft_strlen(str)))
		return (del(&str));
	if (param->flags != NULL && ft_strchr(param->flags, '-'))
	{
		if (!(ft_min_x(&str, "0x")))
			return (del(&str));
	}
	else if (!(ft_put_x(&str, -1, flag, "0x")))
		return (del(&str));
	ft_putstr(str);
	len = ft_strlen(str);
	ft_strdel(&str);
	return (len);
}
