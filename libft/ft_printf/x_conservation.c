/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_conservation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klsirop <klsirop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:17:19 by jmaynard          #+#    #+#             */
/*   Updated: 2020/08/01 17:55:39 by klsirop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_getarg_16(t_flags *param, va_list *arg)
{
	char *str;

	str = NULL;
	if (param->size == NULL)
		str = ft_itoa_base_large(va_arg(*arg, unsigned int), 16);
	else if (param->size != NULL && !ft_strcmp(param->size, "l"))
		str = ft_itoa_base_large(va_arg(*arg, unsigned long int), 16);
	else if (param->size != NULL && !ft_strcmp(param->size, "ll"))
		str = ft_itoa_base_large(va_arg(*arg, unsigned long long int), 16);
	else if (param->size != NULL && !ft_strcmp(param->size, "h"))
		str = ft_itoa_base(((unsigned short int)va_arg(*arg, int)), 16);
	else if (param->size != NULL && !ft_strcmp(param->size, "hh"))
		str = ft_itoa_base(((unsigned char)va_arg(*arg, unsigned int)), 16);
	else if (param->size != NULL && !ft_strcmp(param->size, "j"))
		str = ft_itoa_base_large(va_arg(*arg, uintmax_t), 16);
	else if (param->size != NULL && !ft_strcmp(param->size, "z"))
		str = ft_itoa_base_large(va_arg(*arg, size_t), 16);
	else if (param->size != NULL && !ft_strcmp(param->size, "L"))
		str = ft_itoa_base_large(va_arg(*arg, __uint64_t), 16);
	return (str);
}

int		ft_width(t_flags *param, char **str, int len)
{
	char	*tmp;
	char	*s;

	if (len < param->wid)
	{
		if (!(tmp = ft_strnew((size_t)(param->wid - len + 1))))
			return (0);
		if (param->pres == -1 && ft_strchr(param->flags, '0')
				&& !ft_strchr(param->flags, '-'))
			ft_memset(tmp, '0', (size_t)(param->wid - len));
		else
			ft_memset(tmp, ' ', (size_t)(param->wid - len));
		if (ft_strchr(param->flags, '-'))
			s = ft_append(*str, tmp);
		else
			s = ft_prepend(*str, tmp);
		ft_strdel(&tmp);
		if (!s)
			return (0);
		ft_strdel(str);
		if (!(*str = ft_strdup(s)))
			return (0);
		ft_strdel(&s);
	}
	return (1);
}

int		ft_hastag(t_flags *param, int z, char **str, int flag)
{
	char *s;

	if (param->type == 3)
		s = ft_strdup("0x");
	else
		s = ft_strdup("0X");
	if (!s)
		return (0);
	if (param->flags != NULL && ft_strchr(param->flags, '#')
		&& ft_strlen(*str) && !z)
	{
		if (param->flags != NULL && ft_strchr(param->flags, '-'))
		{
			if (!(ft_min_x(str, s)))
				return (0);
		}
		else if (!(ft_put_x(str, ft_strlen(*str), flag, s)))
			return (0);
	}
	ft_strdel(&s);
	return (1);
}

int		ft_min_x(char **str, char *s)
{
	int		sp;
	char	*tmp;

	sp = ft_spaces(*str);
	if (!(tmp = ft_strjoin(s, *str)))
		return (0);
	ft_strdel(str);
	if (!(*str = ft_strdup(tmp)))
		return (0);
	ft_strdel(&tmp);
	if (sp >= 1)
	{
		if (sp == 1)
			tmp = ft_crop(*str, ft_strlen(*str) - 1);
		else
			tmp = ft_crop(*str, ft_strlen(*str) - 2);
		if (!tmp)
			return (0);
		ft_strdel(str);
		if (!(*str = ft_strdup(tmp)))
			return (0);
		ft_strdel(&tmp);
	}
	return (1);
}

int		x_con(t_flags *param, va_list *arg)
{
	char	*str;
	int		len;
	int		flag;
	int		zero;

	flag = 0;
	zero = 0;
	if (!(str = ft_getarg_16(param, arg)))
		return (0);
	zero = !ft_strcmp("0", str);
	if (!ft_strcmp("0", str) && param->pres == 0)
	{
		str = ft_strdup("");
		zero = 1;
	}
	if ((flag = ft_prescision(param, &str)) < 0)
		return (del(&str));
	if (!ft_width(param, &str, ft_strlen(str)))
		return (del(&str));
	if (!(ft_hastag(param, zero, &str, flag)))
		return (del(&str));
	ft_putstr(str);
	len = ft_strlen(str);
	ft_strdel(&str);
	return (len);
}
