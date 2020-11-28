/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 14:38:11 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/14 17:41:08 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char*)src)[i] != (unsigned char)c)
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		if (((unsigned char*)src)[i] == (unsigned char)c)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			return (dest + i + 1);
		}
		i++;
	}
	if (i == n)
		return (NULL);
	return (dest);
}
