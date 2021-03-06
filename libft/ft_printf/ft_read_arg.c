/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:59:03 by jmaynard          #+#    #+#             */
/*   Updated: 2020/12/01 18:50:04 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_putnstr(const char *s, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		write(g_fd, &s[i], 1);
		i++;
	}
	return (i);
}

char	*ft_prepend(char *dst, char *src)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(dst) + ft_strlen(src) + 1;
	if (!(tmp = (char *)malloc(len * sizeof(char))))
		return (NULL);
	while (*src != '\0')
	{
		tmp[i] = *src;
		src++;
		i++;
	}
	while (*dst != '\0')
	{
		tmp[i] = *dst;
		dst++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_append(char *dst, char *src)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(dst) + ft_strlen(src) + 1;
	if (!(tmp = (char *)malloc(len * sizeof(char))))
		return (NULL);
	while (*dst != '\0')
	{
		tmp[i] = *dst;
		dst++;
		i++;
	}
	while (*src != '\0')
	{
		tmp[i] = *src;
		src++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	ft_read_arg(va_list *arg, char *format, int *val)
{
	char	*tmp;

	if (!ft_strcmp(format, "%"))
		return ;
	if (!(tmp = ft_strchr(format, '%')))
	{
		ft_putstr_fd(format, g_fd);
		*val += ft_strlen(format);
		return ;
	}
	else
	{
		while (format < tmp)
		{
			ft_putchar_fd(*format, g_fd);
			(*val)++;
			format++;
		}
		if (!(format = ft_consver(tmp, arg, val)))
		{
			*val = -1;
			return ;
		}
		ft_read_arg(arg, format, val);
	}
}
