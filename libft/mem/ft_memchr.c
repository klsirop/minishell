/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 14:40:12 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/14 16:40:21 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if ((((unsigned char *)s)[i]) == (unsigned char)c)
			break ;
		i++;
	}
	if (i == n)
		return (NULL);
	return ((void *)(s + i));
}
