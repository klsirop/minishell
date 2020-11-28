/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:54:05 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:20:31 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_valid_pres(char *fmt, t_flags *param, va_list *arg)
{
	param->pres = 0;
	fmt++;
	if (*fmt == '*')
	{
		param->pres = va_arg(*arg, int);
		fmt++;
	}
	else
	{
		if (ft_isdigit(*fmt))
			param->pres = ft_atoi(fmt);
		while (ft_isdigit(*fmt))
			fmt++;
	}
	return (fmt);
}

void	ft_help_valid_flags(t_flags *param)
{
	int i;

	if ((ft_strchr(param->flags, '+') != NULL)
		&& (ft_strchr(param->flags, ' ') != NULL))
	{
		i = 0;
		while (param->flags[i] != '\0')
		{
			if (param->flags[i] == ' ')
				param->flags[i] = '+';
			i++;
		}
	}
	if ((ft_strchr(param->flags, '-') != NULL)
		&& (ft_strchr(param->flags, '0') != NULL))
	{
		i = 0;
		while (param->flags[i] != '\0')
		{
			if (param->flags[i] == '0')
				param->flags[i] = '-';
			i++;
		}
	}
}

char	*ft_valid_flag(char *flags, char *fmt, t_flags *param)
{
	size_t	size;
	char	*tmp;

	size = 0;
	if (param->flags == NULL && ft_strchr(flags, *fmt))
	{
		if (!(param->flags = ft_memalloc(size + 1)))
			return (NULL);
		param->flags[0] = *fmt;
	}
	while (ft_strchr(flags, *fmt) && (size = ft_strlen(param->flags) + 1))
	{
		if (!(tmp = (char *)ft_memalloc(size + 1)))
			return (NULL);
		ft_strcpy(tmp, param->flags);
		tmp[size - 1] = *fmt;
		ft_strdel(&(param->flags));
		if (!(param->flags = ft_strdup(tmp)))
			return (NULL);
		fmt++;
		ft_strdel(&tmp);
	}
	if (param->flags != NULL)
		ft_help_valid_flags(param);
	return (fmt);
}

char	*ft_flags(char *fmt, t_flags *param)
{
	char *flags;

	if (!(flags = ft_strdup("#0- +")))
		return (NULL);
	fmt = ft_valid_flag(flags, fmt, param);
	if ((param->flags != NULL) && (ft_strcmp(param->flags, "error") == 0))
	{
		ft_free_param(param);
		return (NULL);
	}
	ft_strdel(&flags);
	return (fmt);
}
