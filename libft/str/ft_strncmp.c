/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 14:34:01 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/17 16:02:52 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *ch1;
	unsigned char *ch2;

	ch1 = (unsigned char *)s1;
	ch2 = (unsigned char *)s2;
	if (n <= 0)
		return (0);
	while (*ch1 != '\0' && *ch2 != '\0' && n > 1)
	{
		if (*ch1 != *ch2)
			return (*ch1 - *ch2);
		ch1++;
		ch2++;
		n--;
	}
	return (*ch1 - *ch2);
}
