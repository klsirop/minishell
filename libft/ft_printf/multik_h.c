/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multik_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 12:43:45 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:24 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_new_mult_h(char **str, int i, int *des)
{
	int a;

	while (i >= 0)
	{
		if ((((*str)[i] - '0') * 5 + *des) <= 9)
		{
			(*str)[i] = (((*str)[i] - '0') * 5 + *des) + '0';
			*des = 0;
		}
		else
		{
			a = ((*str)[i] - '0') * 5 + *des;
			(*str)[i] = a % 10 + '0';
			*des = a / 10;
		}
		i--;
	}
}

int		ft_new_mult_hh(char **str, int des, int *count)
{
	char *tmp;
	char *tmp1;

	if (des != 0)
	{
		if (!(tmp1 = ft_itoa(des)))
			return (-1);
		if (!(tmp = ft_strjoin(tmp1, *str)))
			return (-1);
		ft_strdel(&tmp1);
		ft_strdel(str);
		if (!((*str) = ft_strdup(tmp)))
			return (-1);
		ft_strdel(&tmp);
	}
	if ((int)ft_strlen(*str) < *count + 1)
	{
		if (!(tmp = ft_strjoin("0", *str)))
			return (-1);
		ft_strdel(str);
		if (!(*str = ft_strdup(tmp)))
			return (-1);
		ft_strdel(&tmp);
	}
	return (0);
}

int		ft_new_mult(char **str)
{
	int			i;
	int			des;
	static int	count;

	if (str == NULL)
	{
		count = 0;
		return (0);
	}
	i = ft_strlen(*str);
	i--;
	des = 0;
	count++;
	ft_new_mult_h(str, i, &des);
	if (ft_new_mult_hh(str, des, &count) == -1)
		return (-1);
	return (0);
}

void	ft_kek(char **str, char c, size_t size)
{
	size_t i;

	i = 0;
	while (*str && (i < size))
	{
		(*str)[i] = c;
		i++;
	}
	(*str)[i] = '\0';
}

char	*ft_equal_h(char **tmp, char *str, char *ost)
{
	char	*tmp1;
	int		lo;
	int		ls;

	tmp1 = NULL;
	lo = ft_strlen(ost);
	ls = ft_strlen(str);
	if (lo > ls)
	{
		if (!(tmp1 = ft_strjoin(str, *tmp)))
			return (NULL);
		ft_strdel(tmp);
	}
	else if (lo < ls)
	{
		if (!(tmp1 = ft_strjoin(ost, *tmp)))
			return (NULL);
		ft_strdel(tmp);
	}
	return (tmp1);
}
