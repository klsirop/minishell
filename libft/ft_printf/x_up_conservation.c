/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_up_conservation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:33:40 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:23:04 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_spaces(char *str)
{
	int i;
	int sp;

	i = -1;
	sp = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == ' ')
			sp++;
	}
	return (sp);
}

char	*ft_difference(char **str, int d, char *c)
{
	char *s;
	char *tmp;
	char *r;

	r = NULL;
	if (!(s = ft_strjoin(c, *str + d)))
		return (NULL);
	if (!(tmp = ft_strdup(s)))
		return (NULL);
	ft_strdel(&s);
	if (d == 1)
		return (tmp);
	if (d >= 2)
	{
		if (!(s = (char *)ft_memalloc(d - 1)))
			return (NULL);
		ft_memset(s, ' ', d - 2);
		if (!(r = ft_strjoin(s, tmp)))
			return (NULL);
		ft_strdel(&tmp);
		ft_strdel(&s);
	}
	return (r);
}

int		ft_eq(char **str, char **tmp, int flag, char *c)
{
	if (((*str)[0] == '0' || (*str)[0] == ' ')
		&& ((*str)[1] == '0' || (*str)[1] == ' ') && !flag)
		*tmp = ft_strjoin(c, *str + 2);
	else
		*tmp = ft_strjoin(c, *str);
	if (!tmp)
		return (0);
	return (1);
}

void	ft_up(char *str)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(str);
	while (i <= len)
	{
		if (ft_isalpha(str[i]))
			str[i] = ft_toupper(str[i]);
		i++;
	}
}

int		x_up_con(t_flags *param, va_list *arg)
{
	char		*str;
	int			len;
	int			i;
	int			zero;

	zero = 0;
	if (!(str = ft_getarg_16(param, arg)))
		return (0);
	zero = !ft_strcmp("0", str);
	if (!ft_strcmp("0", str) && param->pres == 0)
	{
		str = ft_strdup("");
		zero = 1;
	}
	ft_up(str);
	if ((i = ft_prescision(param, &str)) < 0)
		return (del(&str));
	if (!ft_width(param, &str, ft_strlen(str)))
		return (del(&str));
	if (!(ft_hastag(param, zero, &str, i)))
		return (del(&str));
	ft_putstr(str);
	len = ft_strlen(str);
	ft_strdel(&str);
	return (len);
}
