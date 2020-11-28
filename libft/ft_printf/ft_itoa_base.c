/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klsirop <klsirop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 18:42:15 by jmaynard          #+#    #+#             */
/*   Updated: 2020/08/01 17:55:02 by klsirop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static size_t	digit_count_large(uintmax_t nb, int base)
{
	size_t		i;

	i = 0;
	while (nb)
	{
		nb /= base;
		i++;
	}
	return (i);
}

char			*ft_itoa_base_large(uint64_t value, int base)
{
	char	*ret;
	char	*tab_base;
	int		taille;
	int		i;

	if (value == 0)
	{
		ret = ft_strdup("0");
		return (ret);
	}
	if (!(tab_base = ft_strdup("0123456789abcdef")))
		return (NULL);
	taille = digit_count_large(value, base);
	if (!(ret = (char *)malloc(sizeof(char) * (taille + 1))))
		return (NULL);
	i = 1;
	while (value != 0)
	{
		ret[taille - i++] = tab_base[value % base];
		value /= base;
	}
	ret[taille] = '\0';
	ft_strdel(&tab_base);
	return (ret);
}

static size_t	digit_count(unsigned short nb, int base)
{
	size_t		i;

	i = 0;
	while (nb)
	{
		nb /= base;
		i++;
	}
	return (i);
}

char			*ft_itoa_base(unsigned short value, int base)
{
	char	*ret;
	char	*tab_base;
	int		taille;
	int		i;

	if (value == 0)
	{
		ret = ft_strdup("0");
		return (ret);
	}
	if (!(tab_base = ft_strdup("0123456789abcdef")))
		return (NULL);
	taille = digit_count(value, base);
	if (!(ret = (char *)malloc(sizeof(char) * (taille + 1))))
		return (NULL);
	i = 1;
	while (value != 0)
	{
		ret[taille - i++] = tab_base[value % base];
		value /= base;
	}
	ret[taille] = '\0';
	ft_strdel(&tab_base);
	return (ret);
}
