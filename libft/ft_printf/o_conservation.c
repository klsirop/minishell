/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_conservation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 17:58:44 by jmaynard          #+#    #+#             */
/*   Updated: 2020/12/01 18:46:15 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_getarg_8(t_flags *param, va_list *arg)
{
	char *str;

	str = NULL;
	if (param->size == NULL)
		str = ft_itoa_base_large(va_arg(*arg, unsigned int), 8);
	else if (param->size != NULL && !ft_strcmp(param->size, "l"))
		str = ft_itoa_base_large(va_arg(*arg, unsigned long int), 8);
	else if (param->size != NULL && !ft_strcmp(param->size, "ll"))
		str = ft_itoa_base_large(va_arg(*arg, unsigned long long int), 8);
	else if (param->size != NULL && !ft_strcmp(param->size, "h"))
		str = ft_itoa_base(((unsigned short int)va_arg(*arg, int)), 8);
	else if (param->size != NULL && !ft_strcmp(param->size, "hh"))
		str = ft_itoa_base(((unsigned char)va_arg(*arg, unsigned int)), 8);
	else if (param->size != NULL && !ft_strcmp(param->size, "j"))
		str = ft_itoa_base_large(va_arg(*arg, uintmax_t), 8);
	else if (param->size != NULL && !ft_strcmp(param->size, "z"))
		str = ft_itoa_base_large(va_arg(*arg, size_t), 8);
	else if (param->size != NULL && !ft_strcmp(param->size, "L"))
		str = ft_itoa_base_large(va_arg(*arg, __uint64_t), 8);
	return (str);
}

int		ft_hash(char **str, t_flags *param)
{
	char *tmp;
	char *s;

	if (param->flags != NULL && ft_strchr(param->flags, '#')
		&& (*str)[0] != '0')
	{
		if (!(tmp = ft_strdup("0")))
			return (0);
		if (!(s = ft_prepend(*str, tmp)))
			return (0);
		ft_strdel(&tmp);
		ft_strdel(str);
		if (!(*str = ft_strdup(s)))
			return (0);
		ft_strdel(&s);
	}
	return (1);
}

int		ft_opres(t_flags *param, int len, char **str)
{
	char *tmp;
	char *s;

	if (len < param->pres)
	{
		if (!(tmp = ft_strnew((size_t)(param->pres - len + 1))))
			return (0);
		ft_memset(tmp, '0', (size_t)(param->pres - len));
		if (!(s = ft_prepend(*str, tmp)))
			return (0);
		ft_strdel(&tmp);
		ft_strdel(str);
		if (!(*str = ft_strdup(s)))
			return (0);
		ft_strdel(&s);
	}
	return (1);
}

int		ft_owid(t_flags *param, char **str, int len)
{
	char *tmp;
	char *s;

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
		ft_strdel(str);
		if (!s)
			return (0);
		if (!(*str = ft_strdup(s)))
			return (0);
		ft_strdel(&s);
	}
	return (1);
}

int		o_con(t_flags *param, va_list *arg)
{
	char	*str;
	int		len;

	if (!(str = ft_getarg_8(param, arg)))
		return (0);
	if (param->pres == 0 && !ft_strcmp(str, "0"))
		if (!(str = ft_strdup("")))
			return (0);
	if (!ft_hash(&str, param))
		return (0);
	if (!(ft_opres(param, ft_strlen(str), &str)))
		return (0);
	if (!(ft_owid(param, &str, ft_strlen(str))))
		return (0);
	ft_putstr_fd(str, g_fd);
	len = ft_strlen(str);
	ft_strdel(&str);
	return (len);
}
