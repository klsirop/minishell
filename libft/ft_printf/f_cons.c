/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 10:47:20 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:20:59 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_round_h(char **mant, int *i, int *cut)
{
	while (((*mant)[*i] == '9') && (*i > 0))
	{
		if ((*mant)[*i - 1] == '-')
			break ;
		(*mant)[*i] = '0';
		(*i)--;
		if ((*mant)[*i] == '.')
			(*i)--;
	}
	if (((*i == 0) && ((*mant)[*i] == '9')) ||
		(((*mant)[0] == '-') && ((*mant)[*i] == '9')))
	{
		if ((*mant)[0] == '-')
		{
			if (ft_min_od_nul(mant) == -1)
				return (-1);
		}
		else if (ft_min_od_nul_rev(mant, i) == -1)
			return (-1);
		(*cut)++;
	}
	return (0);
}

int		ft_round(char **mant, int i)
{
	int		cut;
	char	*tmp;

	cut = i;
	if ((*mant)[i] >= '5')
	{
		i--;
		if ((*mant)[i] == '.')
			i--;
		if (ft_round_h(mant, &i, &cut) == -1)
			return (-1);
		(*mant)[i]++;
	}
	if (!(tmp = ft_crop(*mant, cut)))
		return (-1);
	ft_strdel(mant);
	if (!(*mant = ft_strdup(tmp)))
		return (-1);
	ft_strdel(&tmp);
	return (0);
}

int		ft_put_zero(char **mant, int pres)
{
	char *kek;
	char *tmp;

	if (!(kek = (char *)malloc(sizeof(char) * (pres + 1))))
		return (-1);
	ft_kek(&kek, '0', pres);
	if (!(tmp = ft_strjoin(*mant, kek)))
		return (-1);
	ft_strdel(mant);
	ft_strdel(&kek);
	if (!(*mant = ft_strdup(tmp)))
		return (-1);
	ft_strdel(&tmp);
	return (0);
}

int		ft_f_pres_h(char **mant, t_flags *param, int *i, int *t)
{
	char *tmp;

	if (*t == 0)
	{
		if ((*mant)[*i] != '\0')
		{
			if (ft_round(mant, *i) == -1)
				return (-1);
			if ((param->pres == 0) && (!(param->flags) || ((param->flags) &&
				!(ft_strchr(param->flags, '#')))))
			{
				if (!(tmp = ft_crop(*mant, ft_strlen(*mant) - 1)))
					return (-1);
				ft_strdel(mant);
				if (!(*mant = ft_strdup(tmp)))
					return (-1);
				ft_strdel(&tmp);
			}
		}
	}
	else if (ft_put_zero(mant, *t) == -1)
		return (-1);
	return (0);
}

int		ft_f_pres(char **mant, t_flags *param)
{
	int		i;
	int		t;

	i = 0;
	while (*mant && (*mant)[i] != '.')
		i++;
	i++;
	t = param->pres;
	while ((t > 0) && ((*mant)[i] != '\0'))
	{
		i++;
		t--;
	}
	if (ft_f_pres_h(mant, param, &i, &t) == -1)
		return (-1);
	return (0);
}
