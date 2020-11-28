/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:48:51 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:20:35 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_hhvl1(t_flags *param, char **tmp)
{
	char *tmp1;

	tmp1 = NULL;
	if (param->size[0] == 'h' && param->size[1] == 'h')
	{
		if (!(tmp1 = ft_strdup("hh")))
			return (0);
		ft_strdel(tmp);
		if (!(*tmp = ft_strdup(tmp1)))
			return (0);
	}
	if (param->size[0] == 'l' && param->size[1] == 'l')
	{
		if (!(tmp1 = ft_strdup("ll")))
			return (0);
		ft_strdel(tmp);
		if (!(*tmp = ft_strdup(tmp1)))
			return (0);
	}
	ft_strdel(&tmp1);
	return (-1);
}

int		ft_hvl1(t_flags *param, char **tmp)
{
	if (param->size[0] == 'l')
	{
		if (!(*tmp = ft_strdup("l")))
			return (0);
	}
	if (param->size[0] == 'h')
	{
		if (!(*tmp = ft_strdup("h")))
			return (0);
	}
	return (ft_hhvl1(param, tmp));
}

int		ft_hvl2(t_flags *param, char **tmp)
{
	if (param->size[0] == 'j')
	{
		if (!(*tmp = ft_strdup("j")))
			return (0);
	}
	else if (param->size[0] == 'z')
	{
		if (!(*tmp = ft_strdup("z")))
			return (0);
	}
	else if (param->size[0] == 'L')
	{
		if (!(*tmp = ft_strdup("L")))
			return (0);
	}
	else
		return (-1);
	return (1);
}

int		ft_help_valid_len(t_flags *param)
{
	char	*tmp;
	int		a;
	int		b;

	if (param->size != NULL)
	{
		a = ft_hvl1(param, &tmp);
		b = ft_hvl2(param, &tmp);
		if (a == 0 || b == 0)
			return (0);
		ft_strdel(&(param->size));
		if (!(param->size = ft_strdup(tmp)))
			return (0);
		ft_strdel(&tmp);
	}
	return (1);
}

char	*ft_valid_len(char *len, char *fmt, t_flags *param)
{
	size_t	size;
	char	*tmp;

	size = 0;
	if (ft_strchr(len, *fmt) && param->size == NULL)
	{
		if (!(param->size = ft_memalloc(size + 1)))
			param->size[0] = *fmt;
	}
	while (ft_strchr(len, *fmt) && ++size)
	{
		if (!(tmp = (char *)ft_memalloc(size + 1)))
			return (NULL);
		tmp = ft_strcpy(tmp, param->size);
		tmp[size - 1] = *fmt;
		ft_strdel(&(param->size));
		if (!(param->size = ft_strdup(tmp)))
			return (NULL);
		fmt++;
		ft_strdel(&tmp);
	}
	if (!ft_help_valid_len(param))
		return (NULL);
	return (fmt);
}
