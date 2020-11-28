/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:50:03 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:20 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_find_a(const char *s, int c, int val)
{
	int i;

	if (s == NULL)
		return (0);
	i = 0;
	while (i < val)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_min_od_nul(char **mant)
{
	char *tmp;

	if (!(tmp = ft_strjoin("-00", *mant + 2)))
		return (-1);
	ft_strdel(mant);
	if (!(*mant = ft_strdup(tmp)))
		return (-1);
	ft_strdel(&tmp);
	return (0);
}

int		ft_min_od_nul_rev(char **mant, int *i)
{
	char *tmp;

	(*mant)[*i] = '0';
	if (!(tmp = ft_strjoin("0", *mant)))
		return (-1);
	ft_strdel(mant);
	if (!(*mant = ft_strdup(tmp)))
		return (-1);
	ft_strdel(&tmp);
	return (0);
}

int		ft_line_var(char **tmp, char **mant)
{
	char *str;

	if (!(str = ft_strjoin("0.", *tmp + 1)))
		return (-1);
	*mant = ft_strdup(str);
	ft_strdel(&str);
	ft_strdel(tmp);
	return (0);
}
